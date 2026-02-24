#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stdlib.h>
#include "../ticket/ticket.h"

int get_reg_number(); // Funcion para generar el numero de radicado aleatorio
bool request_email(char* email); // Funcion para solicitar email
bool request_id(int* id); // Funcion para solicitar id
bool request_text(char* text, char* var, int size); // Funcion para solicitar texto
bool request_ticket(char* t); // Funcion para solicitar descripcion ticket
bool request_number(char* text, int* var); // Funcion para solicitar numero
int get_type(); // Funcion para solicitar el tipo de ticket
void create_assets_file(Ticket* t); // Funcion para crear el archivo de activos
char* translate_type(int type); // Funcion para traducir el tipo de ticket

#endif