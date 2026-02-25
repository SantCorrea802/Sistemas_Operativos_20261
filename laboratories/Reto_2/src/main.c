#include "../include/ticket/ticket.h"
#include "../include//utils/utils.h"
#include <stdbool.h>

int main() {

  printf("\n\t¡Bienvenido/a!\n");
  while(true){
    printf("\n\t1. Crear ticket\n");
    printf("\n\t2. Salir\n");
    printf("\n\tIngrese su opcion: ");
    int option;
    while (!request_number("su opcion: ", &option)) {
      printf("\tOpcion invalida. Intente de nuevo.\n");
    }
    if (option == 1){
      Ticket* t;
      t = create_ticket();
      printf("\n");
      printf("\nradicado: %d\n", t->reg_number);
      printf("id: %d\n", t->id);
      printf("email: %s\n", t->email);
      printf("tipo: %d\n", t->type);
      delete_ticket(t);
    }
    if(option == 2){
      break;
    }
  }



}