*Este proyecto ha sido creado como parte del currículo de 42 por alavryk.*

## Descripción
`get_next_line` es una función en C que lee y devuelve una línea a la vez desde un descriptor de archivo (`fd`), ya sea un archivo de texto o la entrada estándar (`stdin`). El proyecto introduce el uso de variables estáticas y la gestión dinámica de memoria sin fugas. Incluye la parte bonus para gestionar múltiples descriptores de archivo de forma simultánea con una única variable estática.

## Algoritmo y justificación
Se utiliza un array estático de punteros (`static char *stash[MX_FD]`) indexado por el descriptor de archivo para conservar los bytes sobrantes entre llamadas sin perder el hilo de lectura de cada `fd`. Se eligió este enfoque frente a las listas enlazadas por su acceso directo en tiempo constante O(1) y su menor sobrecarga de memoria.

El flujo en cada llamada sigue tres pasos:
1. **Lectura (`read_stash`):** Lee bloques de tamaño `BUFFER_SIZE` y los concatena en `stash[fd]` hasta encontrar un salto de línea (`\n`) o llegar al final del archivo (`EOF`).
2. **Extracción (`ft_strim`):** Copia los caracteres desde el inicio de `stash[fd]` hasta el primer `\n` (inclusive) para formar la línea que se devolverá.
3. **Limpieza (`ft_clean`):** Guarda en una nueva asignación el texto restante posterior al `\n` y libera el bloque anterior.

## Instrucciones
Para compilar el proyecto junto con tu archivo `main.c` de pruebas, ejecuta:

```bash
# Parte obligatoria
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl

# Parte bonus
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main.c -o gnl_bonus
```

El parámetro `BUFFER_SIZE` es opcional; si no se especifica, el código usa un valor por defecto de `10`.

## Recursos
* Documentación del sistema Unix (`man 2 read`, `man 3 malloc`, `man 3 free`).
* Documentación del lenguaje C sobre almacenamiento y ciclo de vida de variables estáticas (`static`).
* **Uso de IA:** Se ha utilizado asistencia de IA para revisar casos borde en la gestión de memoria (fallos de `malloc` y `read`), estructurar el proceso de depuración con Valgrind/testers y redactar este documento.
