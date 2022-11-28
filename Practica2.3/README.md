# Práctica 2.3 Procesos

## Creación y atributos de ficheros

### ************** Ejercicio 1 **************
<pre>
<code>$man chrt</code>
</pre>
Sirve para consultar la planificación y prioridad de un proceso.

<code>$chrt -v -p </code>

Para cambiar la planificación 
<pre>
<code>
$chrt -o -p <pid> #SCHED_OTHER
$chrt -f -p <pid> #SCHED_FIFO
$chrt -r -p <pid> #SCHED_RR
</code>
</pre>

