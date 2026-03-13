#ifndef UTILS_H
#define UTILS_H

#include "../queue/queue.h"
#include <stdbool.h>

// algoritmo RR
void roundRobin(Queue* queues[], int queue_index, int* current_time, Process* finished_processes[], int* finished_count);

Queue* saveQueuesInList(int num_queues, int* quantums);

Queue* requestQueue();

void managePriorities(Queue* queues, int num_queues, int current_time);


bool request_number(char* text, int* var);

#endif