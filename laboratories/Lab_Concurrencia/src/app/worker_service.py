from app.config import Settings
from app.db import open_connection
from app.processor import process_task
from app.repository import Task, TaskRepository
from app.shared_log import SharedLogger


def claim_task(settings: Settings, logger: SharedLogger) -> Task | None:
    conn = open_connection(settings)
    conn.autocommit = False

    try:
        repo = TaskRepository(conn)
        task = repo.claim_next_task()
        conn.commit()

        if task is not None:
            logger.write(settings.worker_id, f"claimed input_id={task.id}")

        return task

    except Exception:
        conn.rollback()
        raise

    finally:
        conn.close()


def save_success(
    settings: Settings,
    logger: SharedLogger,
    task: Task,
    result: str,
) -> None:
    conn = open_connection(settings)
    conn.autocommit = False

    try:
        repo = TaskRepository(conn)
        repo.save_success(task, settings.worker_id, result)
        conn.commit()

        logger.write(settings.worker_id, f"processed input_id={task.id}")

    except Exception:
        conn.rollback()
        raise

    finally:
        conn.close()


def save_failure(
    settings: Settings,
    logger: SharedLogger,
    task: Task,
    error: Exception,
) -> None:
    conn = open_connection(settings)
    conn.autocommit = False

    try:
        repo = TaskRepository(conn)
        repo.save_failure(task)
        conn.commit()

        logger.write(
            settings.worker_id,
            f"failed input_id={task.id} error={repr(error)}",
        )

    except Exception as fallback_error:
        conn.rollback()

        logger.write(
            settings.worker_id,
            (
                f"failed to mark failure input_id={task.id} "
                f"error={repr(fallback_error)}"
            ),
        )

    finally:
        conn.close()


def run_worker(settings: Settings, logger: SharedLogger) -> None:
    logger.write(settings.worker_id, "started")

    while True:
        task = claim_task(settings, logger)

        if task is None:
            logger.write(settings.worker_id, "no pending tasks")
            break

        try:
            result = process_task(task)
            save_success(settings, logger, task, result)

        except Exception as exc:
            save_failure(settings, logger, task, exc)

    logger.write(settings.worker_id, "finished")