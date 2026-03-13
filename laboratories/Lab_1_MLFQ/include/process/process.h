#ifndef PROCESS_H
#define PROCESS_H
typedef struct Queue Queue;

typedef struct Process{
    int id; // PID
    int arrival_time; // Tiempo de llegada
    int burst_time; // Cuanto tiempo de ejecucion tiene o necesita
    int remaining_time; // Cuanto tiempo de ejecucion le falta
    int start_time; // En que tiempo empezo a ejecutarse
    int finish_time; // En que tiempo termino su ejecucion
    double first_response_time; // response time
    Queue* current_queue; // Cola en la que actualmente está

} Process;

static int process_id_counter = 0;

// Constructor
Process* createProcess(int arrival_time, int burst_time);


// Getters y Setters
int getId(Process* process);
int getArrivalTime(Process* process);
int getBurstTime(Process* process);
int getRemainingTime(Process* process);
int getStartTime(Process* process);
int getFinishTime(Process* process);
double getFirstResponseTime(Process* process);

void setId(Process* process, int new_id);
void setArrivalTime(Process* process, int new_arrival_time);
void setBurstTime(Process* process, int new_burst_time);
void setRemainingTime(Process* process, int new_remaining_time);
void setStartTime(Process* process, int new_start_time);
void setFinishTime(Process* process, int new_finish_time);
void setFirstResponseTime(Process* process, int new_first_response_time);




void deleteProcess(Process* process);

void exportProcessToCSV(Process* process, const char* filename);

#endif