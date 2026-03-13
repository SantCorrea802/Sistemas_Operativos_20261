#ifndef QUEUE_H
#define QUEUE_H

#include "../process/process.h"

typedef struct Queue {
    int id; // identificador de la cola
    int quantum; // duracion del quantum en milisegundos
    int priority; // 0 Es maxima prioridad....
    Process* processes; // arreglo de procesos en la cola
    int size; // cantidad de procesos en la cola
    
} Queue;

Queue* createQueue(int quantum, int priority);

// Getters y setters
int getQuantum(Queue* queue);
void setQuantum(Queue* queue, int new_quantum);
int getPriority(Queue* queue);
void setPriority(Queue* queue, int new_priority);
int getSize(Queue* queue);


// Insertar un proceso a la cola
void insertProcess(Queue* queue, Process* process, int current_time);

// Quitar un proceso de la cola
Process* removeProcess(Queue* queue);

void moveProcessAnotherQueue(Queue* sender_queue, Queue* receiver_queue, Process* process, int current_time);

// Destructor
void deleteQueue(Queue* queue);

#endif