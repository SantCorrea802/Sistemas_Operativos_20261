import psycopg2
from psycopg2.extensions import connection

from app.config import Settings


def open_connection(settings: Settings) -> connection:
    return psycopg2.connect(
        host=settings.db_host,
        port=settings.db_port,
        dbname=settings.db_name,
        user=settings.db_user,
        password=settings.db_password,
    )