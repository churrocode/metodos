TP 2 - Grupo 14
-----------------

Para reproducir los experimentos se debe compilar el objetivo main (make main).
Este ejecutable recibe como primer parámetro el archivo con los datos de entrada y como segundo un 0 para ejecutar las mediciones de span variable, o un 1 para variar las cargas. Los resultados se escriben en los archivos .out.

Para compilar la heurística de la competencia, se debe compilar el objetivo competencia (make competencia).
Este ejecutable interactúa con los archivos de entrada y salida según lo especificado por la cátedra.

Puente.h contiene la clase Puente, que modela el problema del puente. Una vez creado un puente (con el único constructor provisto, que toma los parámetros descriptos en el enunciado). Para resolver el sistema pedido, primero se debe ejecutar Puente.generarMatriz() para crear la matriz asociada al sistema y luego Puente.resolverPuente() para triangularla y obtener una solución. Además, después se pueden consultar si el puente es seguro para los parámetros de entrada mediante Puente.esSeguro().

MatrizBanda.h contiene la representación de una matriz esparsa, cuyas operaciones comentamos en el informe. En general no utiliza el hecho de ser una matriz con bandas, excepto para la triangulación.


