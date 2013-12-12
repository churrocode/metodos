#!/bin/bash

#variamos c en {0.2,0.5,0.8,0.95}
#usamos el grafo que provee http://snap.stanford.edu/data/web-BerkStan.html, contiene 685230 paginas y 7600595 links
#Descargar el tar.gz de la página y extraerlo en la carpeta parser, notar que el archivo tiene comentarios, eliminarlos, y dejar en la primer linea
#la cantidad de paginas y en la segunda la cantidad de links para que main.cpp parsee bien el archivo.

#Para cada c se mide la evolucion del error y tiempo de ejecucion

for c in 0.2 0.5 0.8 0.95
do
    ./main ../parser/web-BerkStan.txt $c 0 1 #sin usar Quadratic Extrapolation
    ./main ../parser/web-BerkStan.txt $c 1 1 #usando Quadratic Extrapolation
done