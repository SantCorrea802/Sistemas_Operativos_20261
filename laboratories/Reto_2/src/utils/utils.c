#include <stdbool.h>
#include "../../include/utils/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



int get_reg_number() {
    
    static int initialized = 0;
    if(initialized == 0){ // Si es la primera vez
        srand(time(NULL)); // creamos la semilla
        initialized = 1; // marcamos como si ya inicializado
    }
    return rand() % 1000000;   // Retornar el numero aleatorio de 0 a 999999
}

bool request_text(char* text, char* var, int size){

    printf("\nIngrese %s", text); // Se pide ingresar el dato necesario
    if (fgets(var, size, stdin) == NULL){ // Si hay un error al leer el dato
        return false;
    }

    for (int i = 0; var[i] != '\0'; i++){ // recorremos cada caracter del email
        if(var[i] == '\n'){ // Si encontramos un \n
            var[i] = '\0'; // lo reemplazamos por un \0 para que quede como final
            break;
        }
    }

    return true; // retornamos true si todo salio bien
}

bool request_number(char* text, int* var){

    char aux[100]; // variable auxiliar para leer el numero como texto
    char* endptr; // Para pasarla a la funcion strtol

    printf("\nIngrese %s", text); // Se pide ingresar el dato necesario
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

bool request_email(char* email){
    if(!request_text("Ingrese su email: ", email, 100)){ // solicitamos email
        printf("\n\tError al leer el email\n"); // Error al leer email
        return false;
    }
    for (int i = 0; email[i] != '\0'; i++){ // recorremos cada caracter del email
        if(email[i] == '@'){
            printf("\n\tEl email es valido\n");
            return true; // si encontramos un @ retornamos true
        }
    }
    printf("\n\tEl email es invalido\n");
    return false; // si no encontramos un @ retornamos false
}


bool request_ticket(char* t){
    if(!request_text("Describa su solicitud: ", t, 256)){ // solicitamos ticket
        printf("\n\tError al leer la solicitud\n"); // Error al leer ticket
        return false;
    }
    return true;
}


bool request_id(int* id){
    if(!request_number("Ingrese su numero de identificacion: ", id)){ // pedir id
        printf("\n\tError al leer el numero de identificacion\n"); // Error al leer id
        return false;
    }
    
    printf("\n\tEl numero de identificacion es valido\n"); // id valido
    return true;
}

int get_type(){
    int type;
    if(!request_number("Ingrese el tipo de ticket:\n 1. Peticion\n 2. Queja\n 3. Reclamacion\n 4. Sugerencia\n 5. Denuncia\n", &type)){ // pedir tipo
        printf("\n\tError al leer el tipo de ticket\n"); // Error al leer tipo
        return -1;
    }
    return type; // retornar tipo
}


void create_assets_file(Ticket* t){
    FILE* file;

    char name_file[256];
    snprintf(name_file, sizeof(name_file),"assets/ticket_%d.txt", t->reg_number);
    

    if ((file = fopen(name_file, "w"))==NULL){
        printf("\n\tFile opening failed");
        return;
    }
    char desc[256];
    char info[256+strlen(desc)];

    
    if(request_ticket(desc)){
        snprintf(info, sizeof(info),"Radicado: %d\nIdentificacion: %d\nEmail: %s\nTipo: %s\nDescripcion: %s\n", t->reg_number, t->id, t->email, translate_type(t->type), desc);
        size_t r1 = fwrite(info, sizeof(char), strlen(info), file);
        if(r1 != strlen(info)){
            printf("\n\tError al escribir en el archivo\n");
            return;
        }
        fclose(file);
        printf("\n\tArchivo assets/ticket_%d.txt t->reg_number creado exitosamente\n", t->reg_number);
    }
    
}

char* translate_type(int type){
    switch(type){
        case 1:
            return "Peticion";
        case 2:
            return "Queja";
        case 3:
            return "Reclamacion";
        case 4:
            return "Sugerencia";
        case 5:
            return "Denuncia";
        default:
            return "Error";
    }
}