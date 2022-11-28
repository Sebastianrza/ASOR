# Práctica 2.3 Procesos

## Creación y atributos de ficheros

### ************** Ejercicio 1 **************
<pre>
<code>$man chrt</code>
</pre>
Sirve para consultar la planificación y prioridad de un proceso.
<pre>
<code>$chrt -v -p </code>

Para cambiar la planificación 
<pre>
<code>
$chrt -o -p <pid> #SCHED_OTHER
$chrt -f -p <pid> #SCHED_FIFO
$chrt -r -p <pid> #SCHED_RR
</code>
</pre>

<pre>
<code>
$man nice
$man renice
</code>
</pre>

Sirve para modificar la prioridad (modificar el valor nice de un proceso).

<pre>
<code>$sudo nice -n-10 /bin/sh
$sudo chrt -f -p 12 22152
</code></pre>

*********************** **Ejercicio 2** ***********************

[ej2](https://github.com/Sebastianrza/ASOR/blob/main/Practica2.3/Politicas_Planificacion/ej2.c)

*********************** **Ejercicio 3** ***********************

<pre>
<code>$sudo nice -n-10 /bin/sh
$sudo chrt -f -p 12 22152
$gcc -o ej ej2.c
$./ej
</code></pre>


## Grupos de procesos y sesiones Recursos de un proceso
