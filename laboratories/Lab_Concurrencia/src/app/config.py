from dataclasses import dataclass
import os
import socket


@dataclass(frozen=True)
class Settings:
    db_host: str
    db_port: int
    db_name: str
    db_user: str
    db_password: str
    worker_id: str
    shared_log_path: str


def load_settings() -> Settings:
    return Settings(
        db_host=os.getenv("DB_HOST", "db"),
        db_port=int(os.getenv("DB_PORT", "5432")),
        db_name=os.getenv("DB_NAME", "labdb"),
        db_user=os.getenv("DB_USER", "labuser"),
        db_password=os.getenv("DB_PASSWORD", "labpass"),
        worker_id=os.getenv("WORKER_ID", socket.gethostname()),
        shared_log_path=os.getenv("SHARED_LOG_PATH", "/shared/logs/workers.log"),
    )