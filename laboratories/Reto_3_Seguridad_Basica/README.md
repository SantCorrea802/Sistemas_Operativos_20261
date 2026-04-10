# Reto 3 - Seguridad básica (Usuarios y archivos)

Laboratorio sencillo en Bash para administrar usuarios desde consola, cumpliendo los requisitos del documento.

## Estructura

- include/config/app.conf: configuracion general (clave por defecto, vencimiento y mensaje)
- include/messages/warning.txt: ejemplo de mensaje personalizado
- src/main.sh: punto de entrada
- src/user/user.sh: operaciones CRUD de usuarios
- src/policy/policy.sh: sudoers, advertencia de vencimiento y bloqueo por expiracion
- src/utils/validation.sh: validaciones (root, politica de clave)
- Makefile: automatiza ejecucion basica y docker
- Dockerfile: entorno Linux liviano sin interfaz grafica

## Etapa 1 - Preparar entorno

1. Entrar a una distro Linux o contenedor.
2. Ir a la carpeta del reto.
3. Ejecutar:

```bash
make all
```

## Etapa 2 - Ver comandos disponibles

```bash
sudo ./src/main.sh help
```

## Etapa 3 - Crear y listar usuarios

Crear con clave por defecto:

```bash
sudo ./src/main.sh create estudiante1
```

Crear con clave personalizada (debe tener mayuscula y caracter especial, sin espacios):

```bash
sudo ./src/main.sh create estudiante2 "ClaveSegura1!"
```

Listar usuarios del sistema (UID >= 1000):

```bash
sudo ./src/main.sh list-users
```

## Etapa 4 - Bloquear, activar y eliminar

```bash
sudo ./src/main.sh lock estudiante1
sudo ./src/main.sh unlock estudiante1
sudo ./src/main.sh delete estudiante1
```

## Etapa 5 - Sudoers limitado al laboratorio

Permite al usuario ejecutar unicamente el comando del laboratorio via sudo:

```bash
sudo ./src/main.sh add-sudo estudiante2
```

## Etapa 6 - Politica de vencimiento y advertencia

El script ya deja configurado en creacion de usuarios:

- vencimiento maximo de clave en 30 dias
- advertencia 10 dias antes
- bloqueo inmediato al expirar (inactividad 0)
- cambio obligatorio de clave en primer inicio de sesion

Instalar advertencia personalizada al login:

```bash
sudo ./src/main.sh install-warning
```

Revisar y bloquear usuarios con clave vencida:

```bash
sudo ./src/main.sh check-expired
```

## Etapa 7 - Probar en contenedor

```bash
make docker-build
make docker-run
```

Dentro del contenedor, usar los mismos comandos con root.

## Notas

- Solo root puede ejecutar acciones administrativas.
