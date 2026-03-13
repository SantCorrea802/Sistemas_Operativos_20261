#ifndef TICKET_H
#define TICKET_H

#include <stdio.h>

typedef struct {
    int id; // Id del usuario
    char *email; // Email del usuario
    int type; //1:Peticion, 2:Queja, 3:Reclamacion, 4:Sugerencia, 5:Denuncia
    int reg_number; // Numero de radicado del ticket
} Ticket;

Ticket* create_ticket();
void delete_ticket(Ticket* t);

#endif