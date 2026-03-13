#include <stdio.h>
#include <stdbool.h>
#include "../include/queue/queue.h"
#include "../include/process/process.h"
#include "../include/utils/utils.h"

int main(){
    // crear las 3 colas
    Queue* queues[3];
    queues[0] = createQueue(2, 0);  // Q0
    queues[1] = createQueue(4, 1);  // Q1
    queues[2] = createQueue(8, 2);  // Q2

    // Crear procesos 
    Process* processes[4];
    processes[0] = createProcess(0, 8);  // P1: arrival=0, burst=8
    processes[1] = createProcess(1, 4);  // P2: arrival=1, burst=4
    processes[2] = createProcess(2, 9);  // P3: arrival=2, burst=9
    processes[3] = createProcess(4, 5);  // P4: arrival=3, burst=5

    // Array para procesos terminados
    Process* finished_processes[4];
    int finished_count = 0;

    // Crear el archivo CSV con header
    FILE* file = fopen("./assets/results.csv", "w");
    if (file == NULL) {
        printf("Error al crear el archivo CSV.\n");
        return 1;
    }
    fprintf(file, "PID,Arrival,Burst,Start,Finish,Response,Turnaround,Waiting\n");
    fclose(file);

    // Iteracion que simula el tiempo, hasta que todos los procesos se acaben
    int time = 0;
    bool all_processes_finished = false;
    int process_index = 0;  // Para agregar procesos en orden de llegada

    while(!(all_processes_finished)){
        // Agregar procesos que llegan en este tiempo o antes
        while (process_index < 4 && processes[process_index]->arrival_time <= time) {
            insertProcess(queues[0], processes[process_index], time);  // Insertar en Q0 inicialmente
            printf("Proceso P%d agregado a Q0 en t=%d\n", processes[process_index]->id, time);
            process_index++;
        }

        // Seleccionar la cola de mayor prioridad no vacía
        int selected_queue_index = -1;
        for (int i = 0; i < 3; i++) {
            if (queues[i]->size > 0) {
                selected_queue_index = i;
                break;
            }
        }

        if (selected_queue_index != -1) {
            // Ejecutar Round Robin en la cola seleccionada
            roundRobin(queues, selected_queue_index, &time, finished_processes, &finished_count);
        } else {
            // Si no hay procesos para ejecutar, avanzar el tiempo en 1
            time++;
        }

        // Priority boost cada 20 ciclos: mover todos los procesos de vuelta a Q0
        if (time % 20 == 0 && time > 0) {
            printf("Priority boost en t=%d: moviendo todos los procesos a Q0\n", time);
            for (int i = 1; i < 3; i++) {  // Desde Q1 y Q2
                while (queues[i]->size > 0) {
                    Process* p = removeProcess(queues[i]);
                    insertProcess(queues[0], p, time);
                }
            }
        }

        // Verificar si todos los procesos han terminado
        all_processes_finished = true;
        for (int i = 0; i < 3; i++) {
            if (queues[i]->size > 0) {
                all_processes_finished = false;
                break;
            }
        }

        // No incrementar time aquí, ya se hace en roundRobin o en el else
    }

    // Exportar procesos terminados a CSV
    for (int i = 0; i < finished_count; i++) {
        exportProcessToCSV(finished_processes[i], "./assets/results.csv");
    }

    printf("Resultados exportados a ./assets/results.csv\n");

    // Liberar memoria
    for (int i = 0; i < finished_count; i++) {
        deleteProcess(finished_processes[i]);
    }
    for (int i = 0; i < 3; i++) {
        deleteQueue(queues[i]);
    }

    return 0;
}