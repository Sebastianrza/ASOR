# Práctica 2.4.Tuberías

## Tuberías sin nombre

*********************** **Ejercicio 1** ***********************

[Ejercicio 1](https://github.com/Sebastianrza/ASOR/tree/main/Practica2.4/Tuberias_Sin_Nombre/ejercicio1.c)

*********************** **Ejercicio 2** ***********************

[Ejercicio 2](https://github.com/Sebastianrza/ASOR/tree/main/Practica2.4/Tuberias_Sin_Nombre/ejercicio2.c)

## Tuberías con nombre

*********************** **Ejercicio 3** ***********************

*Terminal 1*
<pre>
<code>$man mkfifo
$mkfifo tuberia
$ls -l
&stat tuberia
$echo "Test" > tuberia
</code></pre>

*Terminal 2*
<pre>
<code>$cat tuberia
</code></pre>

*********************** **Ejercicio 4** ***********************

[Ejercicio 4](https://github.com/Sebastianrza/ASOR/tree/main/Practica2.4/Tuberias_Con_Nombre/ejercicio4.c)

## Multiplexión de caneles de entrada y salida


*********************** **Ejercicio 5** ***********************

[Ejercicio 5](https://github.com/Sebastianrza/ASOR/blob/main/Practica2.4/Multiplexacion_Sincrona_ES/ejercicio5.c)

*Terminal 1*
<pre>
<code>$gcc -o ej5 ejercicio5.c
$./ej2
</code></pre>


*Terminal 2*
<pre>
<code>$echo "Test" > tuberia
$echo "Test" > tuberia2
</code></pre>

