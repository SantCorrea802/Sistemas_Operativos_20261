# Laboratorio de Concurrencia

Laboratorio de Sistemas Operativos para demostrar concurrencia entre múltiples contenedores worker usando Docker Compose, PostgreSQL, transacciones y locks.

## Arquitectura

El sistema está compuesto por tres servicios:

- `db`: base de datos PostgreSQL.
- `init-db`: contenedor temporal que ejecuta `db/init.sql`.
- `worker`: contenedor Python que procesa tareas concurrentemente.

Los workers leen tareas desde la tabla `input`, procesan cada tarea y escriben resultados en la tabla `result`.

## Tecnologías usadas

- Docker Compose
- PostgreSQL 16
- Python 3.12
- psycopg2
- Locks de PostgreSQL
- `fcntl.flock` para archivo compartido

## Estructura del proyecto

```text
Lab_Concurrencia/
├── db/
│   └── init.sql
├── shared/
│   └── logs/
├── src/
│   └── app/
│       ├── config.py
│       ├── db.py
│       ├── main.py
│       ├── processor.py
│       ├── repository.py
│       ├── shared_log.py
│       └── worker_service.py
├── docker-compose.yml
├── Dockerfile
└── requirements.txt
```
