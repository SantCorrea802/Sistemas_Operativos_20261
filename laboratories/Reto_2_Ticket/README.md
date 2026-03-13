# Reto #2 Sistemas Operativos 2026-1

### Descripción

Sistema de interfaz de consola que registra tickets de reclamación tipo PQR (Petición, queja, reclamo, sugerencia y denuncia), donde el usuario ingresa su número de identificación, correo electrónico, tipo de ticket y una descripción donde especifique su solicitud, además se generará un id unico y aleatorio (Número de radicado) en formato .txt dentro de la carpeta assets, para diferenciar un ticket de los demás, allí se encontrará la información del usuario, ticket y número de radicado.

### Estructura del proyecto

```
Reto_2
│
├── src/
│ ├── main.c
│ ├── ticket/
│ │ └── ticket.c
│ └── utils/
│ └── utils.c
│
├── include/
│ ├── ticket/
│ │ └── ticket.h
│ └── utils/
│ └── utils.h
│
├── assets/
├── Makefile
└── README.md
```

### Makefile

El proyecto incluye un Makefile que facilita la ejecución, compilación y limpieza del ejecutable, contiene las etiquetas:

* ticket_app: Compila el proyecto
* run: Ejecuta el ejecutable
* clean: Borra el ejecutable
* all: Llama a run para ejecutar el programa

### Explicación técnica del proyecto

#### Uso de punteros y manejo de memoria

Durante el desarrollo se hizo uso de los punteros en bastantes partes del codigo para tambien dar uso del manejo de la memoria con las llamadas malloc y free. Puede verlo en ticket.c al definir una función que sirve como constructor y otra como destructor, para hacer uso de esto se debe utilizar punteros a Ticket y, con las ventajas que este propotciona evitamos fugas de memoria.

Otro caso de punteros en este proyecto es cuando se usa `char* var` para poder hacer un manejo y gestion de textos adecuado, ya que muchas funciones de las librerias de C tienen como parametros punteros al primer elemento de una cadena de texto, además permite verificación de otros procesos como conversion de string a entero o entero a string.

#### Generación del radicado

Para este solo se hizo uso de srand(), rand() y time(NULL).

El flujo o idea es: Inicializar o crear una semilla cada vez que ejecutemos el programa, si ya existe entonces se usa esa misma, si no se ha creado, la creamos con `srand(time(NULL))` Asi nos entrega una semilla totalmente diferente a alguna otra. Luego de este proceso ya podemos retornar un numero el cual se ha puesto modulo 1000000 para tener un numero entre 0 y 999999.

#### Manejo de errores

En este proyecto se hizo cargo de evitar entradas vacias o retornos erroneos.

Para convertir un texto a número se usó strtol el cual nos da el string convertido y un valor en `*endptr` que nos dice si se pudo hacer la conversion correctamente, donde comparamos que si `*endptr != '\0' && *endptr != '\n'` Entonces es porque no lo hizo exitosamente, ya que esta linea nos dice si llegó al final del texto (El final del texto en C tiene uno de esos 2 caracteres).

Otro manejo destacable en este desarrollo, fue a la hora de crear los .txt con la información del ticket. Esta tarea requeria crear y escribir en un archivo, por lo que se dió uso de la función fopen y se manejo la posibilidad de un error de cualquier tipo con:

`if ((file =fopen(name_file, "w"))==NULL)` nos advierte si se ha logrado crear el archivo o no, en caso de que no se muestra un mensaje de error y se sale de la función de crear el archivo .txt.

El resto de errores fueron simples validaciones de ingresar un numero en el rango permitido, que un texto tenga un caracter especifico, etc... que solo se trataron con condicionales if.
