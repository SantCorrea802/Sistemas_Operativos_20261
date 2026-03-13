#include "../../include/ticket/ticket.h"
#include "../../include/utils/utils.h"
#include <stdlib.h>
#include <string.h>


Ticket* create_ticket(){
    Ticket* t = (Ticket*)malloc(sizeof(Ticket));
    char _email[100];
    int _id;
    int _type;
    do{
        _type = get_type();
    }while(_type > 5 || _type < 1);
    while(!request_email(_email));
    while(!request_id(&_id));

    t->id = _id;
    t->email = malloc(strlen(_email) + 1);
    snprintf(t->email, strlen(_email) + 1,"%s", _email);
    t->type = _type;
    t->reg_number = get_reg_number();
    create_assets_file(t);
    
    return t;
}

void delete_ticket(Ticket* t){
    if(t == NULL){
        return;
    }
    free(t->email);
    free(t);
    t = NULL;
}