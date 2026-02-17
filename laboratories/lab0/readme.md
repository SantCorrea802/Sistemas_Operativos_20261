# PASO A PASO RETO 00

### Paso 1: crear un directorio en la ruta ~/operating-systems-20261/laboratories/lab0

mkdir -p ~/operating-systems-20261/laboratories/lab0

### Paso 2: navegar hasta el directorio creado

cd operating-systems-20261/laboratories/lab0

### Paso 3: Imprimir la ruta absoluta del directorio y enviarla al archivo path.txt, ubicado en el directorio creado

pwd > path.txt
verificación: path.txt

### Paso 4: Con un solo comando crear los directorios: example, music, photos y projects

mkdir example music photos projects

### Paso 5: Con un solo comando crear los archivos file1, file2, ..., file100 EN CADA UNO de los directorios recien creados

for c in ~/operating-systems-20261/laboratories/lab0/*/; do
> touch "$c"/file{1..100};
> done

### Paso 6: Con un solo comando borrar los primero 10 y ultimos 20 archivos creados en cada una de las carpetas

for c in ~/operating-systems-20261/laboratories/lab0/*/; do
> rm -f "$c"/file{1..10} "$c"/file{81..100};
> done

### Paso 7: Mover las carpetas example, music y photos dentro de projects

mv example music photos projects

### Paso 8: Borrar todos los archivos dentro de projects a excepcion de los directorios e ingresar el resultado en output.txt

cd projects/
rm -v * > ~/operating-systems-20261/laboratories/lab0/output.txt
verificación: cat output.txt
