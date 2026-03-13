#include "../../include/utils/utils.h"
#include "../../include/queue/queue.h"
#include "../../include/process/process.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void roundRobin(Queue* queues[], int queue_index, int* current_time, Process* finished_processes[], int* finished_count){

    Queue* queue = queues[queue_index];

    // Si la cola no tiene procesos, no se hace nada
    if(queue->size == 0){return;}
    // tomamos el proceso a remover ya que se ha simulado que se ha ejecutado
    Process* process = removeProcess(queue);

    // si el proceso no habia empezado aun su ejecucion, se inicia en 
    if(process->start_time == -1){
        process->start_time = *current_time;
        process->first_response_time = 0.0;
    }

    /* si el tiempo sobrante es menor que el quantum entonces al tiempo sobrante le restamos el mismo sobrante (Significa que ya faltaba ese tiempo sobrante para terminar su ejecucion)
    Si no, entonces al tiempo sobrante le restamos el quantum*/
    int time_slice = (process->remaining_time < queue->quantum) ? process->remaining_time : queue->quantum;
    process->remaining_time -= time_slice;

    printf("\n\t\tEN t = %d SE EJECUTA\n\tPID:%d, Arrival Time: %d, Remaining Time: %d, Start Time: %d", *current_time, process->id, process->arrival_time, process->remaining_time, process->start_time);

    // Incrementar el tiempo por el time_slice
    *current_time += time_slice;

    // Si ya se ha terminado su ejecucion, entonces calculamos response_time
    if (process->remaining_time == 0){
        process->first_response_time = process->start_time - process->arrival_time;
        process->finish_time = *current_time;
        double turnaround = process->finish_time - process->arrival_time;
        double waiting = turnaround - process->burst_time;
        printf(", Finish Time: %d, Response Time: %.2f, Turnaround: %.2f, Waiting: %.2f\n", process->finish_time, process->first_response_time, turnaround, waiting); 
        process->current_queue = NULL;

        // Guardar en finished
        finished_processes[(*finished_count)++] = process;
    } else {
        // Si no terminó, decidir si demover o reinsertar
        if (time_slice == queue->quantum && queue_index < 2) {
            // Democión: consumió todo el quantum, mover a la siguiente cola
            printf(" -> Se movio a Q%d\n", queue_index + 1);
            insertProcess(queues[queue_index + 1], process, *current_time);
        } else {
            // Reinsertar en la misma cola
            printf(" -> Reinsertado en Q%d\n", queue_index);
            insertProcess(queues[queue_index], process, *current_time);
        }
    }


}

// solicitar un numero
bool request_number(char* text, int* var){

    char aux[100]; // variable auxiliar para leer el numero como texto
    char* endptr; // Para pasarla a la funcion strtol

    printf("\n%s", text); // Se pide ingresar el dato necesario
    if (!fgets(aux, 100, stdin)){ // Si hay un error al leer el dato, false
        return false;
    }

    long v = strtol(aux, &endptr, 10); // Convertimos el texto a numero

    if (aux == endptr){ // si apuntan a la misma direccion de memoria, significa que no se pudo convertir el texto a numero
        return false;
    }else{
        if (*endptr != '\0' && *endptr != '\n') { // Si no se llegó al final de la cadena, significa que se encontraron caracteres no numéricos
            return false;
        }
    }

    *var = (int)v; // volvemos a convertir el numero a int

    return true; // retornamos true si todo salio bien
}

// Funcion que pide los datos para crear la cola
Queue* requestQueue(){
    int quantum, priority;
    request_number("\nIngrese el quantum de la cola: ", &quantum);
    request_number("\nIngrese la prioridad de la cola (0 ES MAXIMA PRIORIDAD): ", &priority);    
    return createQueue(quantum, priority);
}

// Funcion que guarda las colas en una lista de colas
Queue* saveQueuesInList(int num_queues, int* quantums){
    Queue* queues = (Queue*)malloc(num_queues * sizeof(Queue));
    for(int i = 0; i<num_queues;i++){
        queues[i] = *requestQueue();
        queues[i].id = i;
    }
    return queues;
}


/* La siguiente es una funcion que se encarga de gestionar las prioridades de los procesos,
es decir, de mover los procesos a las colas correspondientes dependiendo de su tiempo
de llegada y su tiempo de ejecucion restante*/
void managePriorities(Queue* queues, int num_queues, int current_time){
    for(int i = 0; i<num_queues-1;i++){
        Queue* current_queue = &queues[i];
        Queue* next_queue = &queues[i+1];
        for(int j = 0; j<current_queue->size;j++){
            Process* process = &current_queue->processes[j];
            if(process->remaining_time > 0 && process->arrival_time <= current_time){
                // Si el proceso ya ha llegado y no ha terminado su ejecucion, se mueve a la siguiente cola
                moveProcessAnotherQueue(current_queue, next_queue, process, current_time);
                j--; // Se decrementa j para revisar el proceso que se movio a la siguiente cola, ya que al moverlo, el proceso que estaba en la posicion j+1 ahora esta en la posicion j

                //removeProcess(current_queue);
                ////ahora insertemos el proceso en la siguiente cola
                //insertProcess(next_queue, process, current_time);
                //printf("\n\t\tEN t = %d SE MUEVE A LA COLA %d\n\tPID:%d, Arrival Time: %d, Remaining Time: %d, Start Time: %d", current_time, next_queue->id, process->id, process->arrival_time, process->remaining_time, process->start_time);


            }
            
        }
    }
}

