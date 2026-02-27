all: ticket_app

clean:
	rm -f ticket_app

ticket_app: src/main.c src/ticket/ticket.c src/utils/utils.c include/ticket/ticket.h include/utils/utils.h
	gcc -o ticket_app src/main.c src/ticket/ticket.c src/utils/utils.c -Wall -Wextra -Iinclude

run: ticket_app
	./ticket_app