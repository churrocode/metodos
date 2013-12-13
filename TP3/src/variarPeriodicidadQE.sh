#!/bin/bash

#Siguiendo utilizando el grafor proveido por http://snap.stanford.edu/data/web-BerkStan.html, variamos la periodicidad con la que aplicamos QE para
#evidenciar una reduccion en el tiempo de ejecucion del metodo de la potencia optimizado pero que sin embargo cuando la periodicidad se acerca a la cantidad de iters original
#sin aplicar QE, vuelve a subir.

for pQE in 5 20 35 50 65 70 90 105 120 135
do
	./main ../parser/web-BerkStan.txt 0.95 1 1 $pQE
done
