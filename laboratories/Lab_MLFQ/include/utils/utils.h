#ifndef UTILS_H
#define UTILS_H

#include "../queue/queue.h"
#include <stdbool.h>

// algoritmo RR
void roundRobin(Queue* queue, int current_time);

Queue* saveQueuesInList(int num_queues, int* quantums);

Queue* requestQueue();

void managePriorities(Queue* queues, int num_queues, int current_time);


bool request_number(char* text, int* var);

#endif