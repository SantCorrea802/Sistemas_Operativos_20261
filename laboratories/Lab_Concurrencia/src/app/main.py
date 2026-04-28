from app.config import load_settings
from app.shared_log import SharedLogger
from app.worker_service import run_worker


def main() -> None:
    settings = load_settings()
    logger = SharedLogger(settings.shared_log_path)

    run_worker(settings, logger)


if __name__ == "__main__":
    main()