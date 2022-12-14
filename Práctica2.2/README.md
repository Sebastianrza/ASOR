# Práctica 2.2 Sistemas de Ficheros

## Creación y atributos de ficheros

### ************** Ejercicio 1 **************

`$man ls`

-a: Muestra todos los archivos (incluidos los ocultos, "." y "..").

-l: Muestra la lista con todos los detalles (Permisos, autores, bytes, fecha de creación de cada archivo).

-d: Muestra la lista de directorios (".").

-h: Muestra los tamaños del archivo en K, M, G (Es necesario: -l o -s).

-i: Muestra el inodo asociado a cada archivo.

-R: Muestra recursivamente todo lo que hay en los directorios.

-1: Muestra un archivo por línea.

-F: Clasifica la salida (con /=>@|).

--color=auto=never: Colorea (o no) la salida del ls según el tipo de archivo.

### ************** Ejercicio 2 **************

`$ls -ld`

drwx------. 20 cursoredes cursoredes 4096 Nov 19 12:08 .

Tipo: Directorio.

rmx_propietario: lectura, escritura y ejecución.

rmx_grupo: ninguno.

rmx_resto: ninguno.

### ************** Ejercicio 3 **************

`$chmod 645 file`

 `$chmod u+rw-x,g+r-wr,o+rx-w file` 
 
### ************** Ejercicio 4 **************
 
 `$mkdir test`
 
 `$chmod -x test`
 
 `$cd test`
 
 resultado: bash: cd:test/: Permiso denegado
 
### ************** Ejercicio 5 **************

[Ejercicio 5](https://github.com/Sebastianrza/ASOR/blob/main/Pr%C3%A1ctica2.2/Creacion_y_Atributos_ficheros/ej5.c)

### ************** Ejercicio 6 **************
 
 `$umask 727`
 
### ************** Ejercicio 7 **************
 
[Ejercicio 7](https://github.com/Sebastianrza/ASOR/blob/main/Pr%C3%A1ctica2.2/Creacion_y_Atributos_ficheros/ej7.c)

### ************** Ejercicio 8 **************
 
 `$ls -i`
 
  `$man stat`
  
### ************** Ejercicio 9 **************
  
[Ejercicio 9](https://github.com/Sebastianrza/ASOR/blob/main/Pr%C3%A1ctica2.2/Creacion_y_Atributos_ficheros/ej9.c)
  
  
### ************** Ejercicio 10 **************

  a) 
    
    $touch fichero
    
    $mkdir directorioP
    
    $ln -s fichero ficheroS
    
    $ln -s directorioP directorioS
    
    $ls -li
    
   <img src="ejercicio10.png">
   
   Se observa que los inodos para cada fichero son diferentes y que los enlaces simbólicos creados vienen representado con una "i" y se muestra a donde apunta.
 
  b)
     
     $ln directorio ldirectorioDuro
     $ln fichero lficheroduro
     $ls -li
     
   <img src="ejercicio10B.png">
   
   No se pueden crear enlaces duros en directorios. Además en la imagen se puede observar que tienen el mismo inodo.
   
   `$stat fichero`
   
   <img src="stat.png">
  c)

      $rm -rf lficheroduro #No pasa nada
      $rm -rf ficherosS #No pasa nada
      $ln lfichero lficheroduro
      $rm -rf fichero #Se corrompe el enlace simbólico.
      
   
### ************** Ejercicio 11 **************

[Ejercicio 11](https://github.com/Sebastianrza/ASOR/blob/main/Pr%C3%A1ctica2.2/Creacion_y_Atributos_ficheros/ej11.c)
      
##  Redirecciones y duplicación de descriptores

### ************** Ejercicio 12 **************

[Ejercicio 12](https://github.com/Sebastianrza/ASOR/blob/main/Pr%C3%A1ctica2.2/Redireccion_y_Duplicacion_descriptores/ej12.c)

### ************** Ejercicio 13 **************

[Ejercicio 13](https://github.com/Sebastianrza/ASOR/blob/main/Pr%C3%A1ctica2.2/Redireccion_y_Duplicacion_descriptores/ej13.c)

ls > dirlist 2>&1: Redirecciona la salida estándar a dirlist y la salida de errores la redirecciona a la 1 que corresponde a dirlist. Ambas salidas se van a ver en dirlist.

ls 2>&1 > dirlist: Redirecciona la salida de error a la salida estándar y la salida estándar a dirlist, los errores se van a ver por pantalla y la salida normal en el fichero dirlist.

##  Cerrojos de ficheros

### ************** Ejercicio 14 **************

`$cat /proc/locks`

<img src="locks.png">

1.- El identificador del bloqueo.

2.- Tipo de bloqueo (POSIX si el bloqueo se hizo con fcntl y FLOCK si se creó con flock.)

3.- Modo de bloqueo (ADVISORY o MANDATORY)

-Advisory: El acceso a los datos está permitido y evita otros bloqueos.

-Mandatory: El acceso a los datos está denegado mientras esté bloqueado.

4.- Tipo de bloqueo (WRITE o READ), correspondiente a bloqueos compartidos o exclusivos.

-Write (Exclusivo): El proceso está escribiendo por lo que no se puede leer ni escribir en el área bloqueada.

-Read (Compartido): El proceso está leyendo por lo que el área no puede ser modificada.

5.- PID del proceso que tiene el bloqueo sobre el fichero.

6.- Tres números separados por :, que identifican el fichero bloqueado.

7.- Byte donde comienza el bloqueo en el fichero.

8.- Byte donde acaba el bloqueo del fichero.

### ************** Ejercicio 15 **************

[Ejercicio 15](https://github.com/Sebastianrza/ASOR/blob/main/Pr%C3%A1ctica2.2/Redireccion_y_Duplicacion_descriptores/ej15.c)

### ************** Ejercicio 16 **************

`$man flock`

Sirve para crear cerrojos en scripst de shell.

##  Directorios

### ************** Ejercicio 17 **************

[Ejercicio 17](https://github.com/Sebastianrza/ASOR/blob/main/Pr%C3%A1ctica2.2/Directorios/ej17.c)
