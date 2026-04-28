import fcntl
import os
from datetime import datetime, timezone


class SharedLogger:
    def __init__(self, path: str):
        self.path = path

    def write(self, worker_id: str, message: str) -> None:
        """
        Escritura protegida sobre archivo compartido.

        flock toma un lock exclusivo sobre el archivo para evitar
        escrituras mezcladas entre contenedores.
        """
        os.makedirs(os.path.dirname(self.path), exist_ok=True)

        timestamp = datetime.now(timezone.utc).isoformat()
        line = f"{timestamp} | {worker_id} | {message}\n"

        with open(self.path, "a", encoding="utf-8") as file:
            fcntl.flock(file.fileno(), fcntl.LOCK_EX)
            try:
                file.write(line)
                file.flush()
                os.fsync(file.fileno())
            finally:
                fcntl.flock(file.fileno(), fcntl.LOCK_UN)