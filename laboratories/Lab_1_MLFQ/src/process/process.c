#include "../../include/process/process.h"
#include <stdlib.h>
#include <stdio.h>

Process* createProcess(int arrival_time, int burst_time){
    Process* process =(Process*)malloc(sizeof(Process));
    process->id = process_id_counter++; //Obtiene un id distinto y va aumentando 1 a 1
    process->arrival_time = arrival_time; // momento de llegada 
    process->burst_time = burst_time; // tiempo que usara la cpu 
    process->remaining_time = burst_time; // al inicio el tiempo que le falta es igual al que necesita
    process->start_time = -1; // de momento no ha iniciado
    process->finish_time = -1; // de momento no ha finalizados
    process->first_response_time = -1.0; // de momento no tiene response time calculado
    process->current_queue = NULL; // aun no está en ninguna cola
    return process;
}//


int getId(Process* process){return process->id;}
int getArrivalTime(Process* process){return process->arrival_time;}
int getBurstTime(Process* process){return process->burst_time;}
int getRemainingTime(Process* process){return process->remaining_time;}
int getStartTime(Process *process){return process->start_time;}
int getFinishTime(Process *process){return process->finish_time;}
double getFirstResponseTime(Process *process){return process->first_response_time;}



void deleteProcess(Process* process){
    free(process);
    free(process->current_queue);
    
}

void exportProcessToCSV(Process* process, const char* filename) {
    FILE* file = fopen(filename, "a"); // Append mode
    if (file == NULL) {
        printf("Error al abrir el archivo %s\n", filename);
        return;
    }
    double turnaround = process->finish_time - process->arrival_time;
    double waiting = turnaround - process->burst_time;
    fprintf(file, "%d,%d,%d,%d,%d,%.2f,%.2f,%.2f\n",
            process->id, process->arrival_time, process->burst_time,
            process->start_time, process->finish_time, process->first_response_time,
            turnaround, waiting);
    fclose(file);
}