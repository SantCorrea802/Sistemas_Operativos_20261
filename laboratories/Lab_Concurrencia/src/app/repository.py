from dataclasses import dataclass
from typing import Optional

from psycopg2.extensions import connection
from psycopg2.extras import RealDictCursor


@dataclass(frozen=True)
class Task:
    id: int
    description: str


class TaskRepository:
    def __init__(self, conn: connection):
        self.conn = conn

    def claim_next_task(self) -> Optional[Task]:
        """
        Reclama una tarea pendiente de forma segura:
        Selecciona una fila pending
        La bloquea con FOR UPDATE SKIP LOCKED
        La marca como in_process
        Retorna la tarea asignada al worker actual
        Esto evita que dos workers tomen el mismo registro
        """
        with self.conn.cursor(cursor_factory=RealDictCursor) as cur:
            cur.execute("""
                WITH candidate AS (
                    SELECT id
                    FROM input
                    WHERE status = 'pending'
                    ORDER BY id
                    LIMIT 1
                    FOR UPDATE SKIP LOCKED
                )
                UPDATE input AS i
                SET status = 'in_process'
                FROM candidate
                WHERE i.id = candidate.id
                RETURNING i.id, i.description;
            """)

            row = cur.fetchone()

            if row is None:
                return None

            return Task(
                id=row["id"],
                description=row["description"],
            )

    def save_success(self, task: Task, worker_id: str, result: str) -> None:
        
        #Guarda el resultado y marca la tarea como procesada Ambas operaciones quedan en la misma transacción
        
        with self.conn.cursor() as cur:
            cur.execute("""
                INSERT INTO result (input_id, worker_identifier, result)
                VALUES (%s, %s, %s);
            """, (task.id, worker_id, result))

            cur.execute("""
                UPDATE input
                SET status = 'processed'
                WHERE id = %s;
            """, (task.id,))

    def save_failure(self, task: Task) -> None:
        with self.conn.cursor() as cur:
            cur.execute("""
                UPDATE input
                SET status = 'failed'
                WHERE id = %s;
            """, (task.id,))