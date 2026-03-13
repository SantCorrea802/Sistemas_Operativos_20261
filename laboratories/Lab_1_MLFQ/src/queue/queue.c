#include "../../include/queue/queue.h"
#include "../../include/process/process.h" 
#include <stdlib.h>


Queue* createQueue(int quantum, int priority){ // Constructor de la cola
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->quantum = quantum;
    queue->priority = priority;
    queue->processes = NULL;
    queue->size = 0;
    queue->id = 0;
    return queue;
}



int getQuantum(Queue* queue){return queue->quantum;}
int getPriority(Queue *queue){return queue->priority;}
int getSize(Queue* queue){return queue->size;}

void setQuantum(Queue *queue, int new_quantum){
    queue->quantum = new_quantum;
}

void setPriority(Queue *queue, int new_priority){
    queue->priority = new_priority;
}


// 
void insertProcess(Queue *queue, Process *process, int current_time){
    process->current_queue = queue; // El proceso pertenece a esta cola
    queue->size++; // El tamaño de la cola crece en uno
    // la lista o arreglo de procesos la aumentamos el tamaño a uno mas
    queue->processes = (Process*)realloc(queue->processes,queue->size * sizeof(Process));
    // insertamos el proceso en la posicion correspondiente
    queue->processes[queue->size - 1] = *process;
}


Process* removeProcess(Queue* queue){
    // si la cola no tiene nada, no hace nada, pues no hay proceso por sacar
    if(queue->size==0){return NULL;}
    // tomamos el proceso que será removido
    Process* removed_process = (Process*)malloc(sizeof(Process));
    // será el proceso de la primera posicion
    *removed_process = queue->processes[0];
    // movemos a los procesos una posicion mas adelante
    for(int i = 1; i<queue->size;i++){
        queue->processes[i-1] = queue->processes[i];
    }
    // reducimos para que tenga un tamaño con un elemento menos
    queue->size--;
    queue->processes = (Process*)realloc(queue->processes, queue->size*sizeof(Process));
    return removed_process;
}

void moveProcessAnotherQueue(Queue* sender_queue, Queue* receiver_queue, Process* process, int current_time){
    if(sender_queue->size == 0){return;} // Si la cola de origen no tiene procesos no se hace nada
    Process* process_to_move = removeProcess(sender_queue);
    if(process_to_move == NULL){return;} // Si no se pudo remover el proceso, no se hace nada
    insertProcess(receiver_queue, process_to_move, current_time);
    

}


void deleteQueue(Queue* queue){
    free(queue->processes);
    free(queue);
}