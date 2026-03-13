## **1\. Objetivo**

Implementar un simulador de scheduler con política Multi-Level Feedback Queue (MLFQ) que incluya: Prioridades entre colas, Diferentes quantums por nivel, Democión por uso completo de quantum, Priority boost periódico, Cálculo de métricas: Waiting time, Turnaround time, Response time y exportar resultados en un archivo .csv.

El estudiante deberá estructurar el proyecto como un sistema pequeño pero formalmente organizado, puede basarse en la estructura del reto 2\.

**2\. Descripción Funcional**

1. Especificación del Scheduler  
   * Estructura de colas  
     1. Q0: prioridad alta, quantum \= 2 ciclos  
     2. Q1: prioridad media, quantum \= 4 ciclos  
     3. Q2: prioridad baja, quantum \= 8 ciclos  
   * Siempre se ejecuta la cola de mayor prioridad no vacía.  
   * Dentro de cada cola se usa Round Robin.  
2. Selección: ejecutar siempre el proceso en la cola de mayor prioridad disponible.  
   * Democión: si un proceso consume todo su quantum, baja un nivel.  
   * No democión: si termina antes de agotar el quantum, no baja.  
   * Priority boost: cada S ciclos (por ejemplo, cada 20 ciclos), todos los procesos vuelven a la cola de mayor prioridad.  
   * La simulación debe ser por ciclos de reloj (tiempo discreto).  
3. Cada proceso debe tener como mínimo:   
   * PID  
   * arrival\_time  
   * burst\_time  
   * remaining\_time  
   * start\_time  
   * finish\_time  
   * first\_response\_time  
   * current\_queue  
4. Métricas obligatorias  
   * Para cada proceso calcular:  
     1. **Response time**: first\_response\_time − arrival\_time  
     2. **Turnaround time**: finish\_time − arrival\_time  
     3. **Waiting time**: turnaround\_time − burst\_time  
5. Salida requerida  
   * Generar un archivo results.csv con el siguiente formato:

   

| PID | Arrival | Burst | Start | Finish | Response | Turnaround | Waiting |
| :---- | :---- | :---- | :---- | :---- | :---- | :---- | :---- |
| P1 | 0 | 10 | 0 |  |  |  |  |
| P2 | 2 | 6 | 4 |  |  |  |  |
| P3 | 4 | 4 | 6 |  |  |  |  |

   

6. Escenario de prueba sugerido  
   * Procesos:  
     1. P1: arrival=0, burst=8  
     2. P2: arrival=1, burst=4  
     3. P3: arrival=2, burst=9  
     4. P4: arrival=3, burst=5  
   * Priority boost cada 20 ciclos.  
7. Análisis:  
   ¿Qué ocurre si el boost es muy frecuente?  
   ¿Qué ocurre si no existe boost?  
   ¿Cómo afecta un quantum pequeño en la cola de mayor prioridad?  
   ¿Puede haber starvation?