DROP TABLE IF EXISTS result;
DROP TABLE IF EXISTS input;

CREATE TABLE input (
    id SERIAL PRIMARY KEY,
    description TEXT NOT NULL,
    status VARCHAR(20) NOT NULL DEFAULT 'pending',
    CONSTRAINT input_status_check
        CHECK (status IN ('pending', 'in_process', 'processed', 'failed'))
);

CREATE TABLE result (
    id SERIAL PRIMARY KEY,
    input_id INT NOT NULL REFERENCES input(id),
    worker_identifier VARCHAR(50) NOT NULL,
    result TEXT NOT NULL,
    date TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP
);

INSERT INTO input (description)
SELECT 'task-' || generate_series(1, 50);