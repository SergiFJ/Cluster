# Cluster

This program represents a Cluster with a organizational chart of CPU and a list of processes and their priority.

In the .hh you will see what does all the possible orders. Those are:
```
configurar_cluster
modificar_cluster
alta_prioridad
baja_prioridad
alta_proceso_espera
alta_proceso_procesador
baja_proceso_procesador
enviar_procesos_cluster
avanzar_tiempo
imprimir_prioridad
imprimir_area_espera
imprimir_procesador
imprimir_procesadores_cluster
imprimir_estructura_cluster
compactar_memoria_procesador
compactar_memoria_cluster
```



## INPUT

The input is a list of CPU with their capacity that represents a binary tree. To represent that in a position there isn't a CPU you have to put '*'. Following that you have to put the number of priorities that exists and their names. Finally, you need to put the orders that you want to execute.

## OUTPUT

The output is the result of the orders and if they could be executed or not.
