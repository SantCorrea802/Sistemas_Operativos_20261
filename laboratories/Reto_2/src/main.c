#include "../include/ticket/ticket.h"
#include <stdbool.h>

int main() {

  printf("\n\t¡Bienvenido/a!\n");
  while(true){
    printf("\n\t1. Crear ticket\n");
    printf("\n\t2. Salir\n");
    printf("\n\tIngrese su opcion: ");
    int option;
    scanf_s("%d", &option);
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


 


  //Ticket* t;
  //t = create_ticket();
//
  //printf("\n");
  //printf("\nradicado: %d\n", t->reg_number);
  //printf("id: %d\n", t->id);
  //printf("email: %s\n", t->email);
  //printf("tipo: %d\n", t->type);
  //return 0;
}