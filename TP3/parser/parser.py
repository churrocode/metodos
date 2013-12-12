import matplotlib.pyplot as pplot

eps = 1.0e-8

def plotearPropagacionDelError():
	# labels = ['c = 0.2', 'c = 0.5', 'c = 0.8', 'c = 0.95']
	# lista_archivos = ['medicionesSinQE0.2.out', 'medicionesSinQE0.5.out', 'medicionesSinQE0.8.out', 'medicionesSinQE0.95.out']
	# lista_archivos = ['medicionesConQE0.2.out', 'medicionesConQE0.5.out', 'medicionesConQE0.8.out', 'medicionesConQE0.95.out']
	labels = ['Sin QE', 'Con QE']
	lista_archivos = ['medicionesSinQE0.95.out', 'medicionesConQE0.95.out']
	i = 0
	for data in  parsearPropagacionDelError(lista_archivos):
		pplot.plot(data.keys(), data.values(), label=labels[i])
		i += 1
	pplot.axhline(eps, linestyle='--', label='Epsilon = {}'.format(str(eps)), c='g')
	pplot.yscale('log')
	pplot.ylabel('Error con la iteracion anterior')
	pplot.xlabel('Cantidad de iteraciones')
	pplot.legend()
	pplot.show()

def parsearPropagacionDelError(lista_archivos):
	for archivo in lista_archivos:
		f = open(archivo, 'r')
		data = {}
		i = 0
		for line in f:
			if i == 0:
				cant_nodos = int(line)
			elif i == 1:
				cant_links = int(line)
			else:
				if line.count(' ') == 1:
					num_iter, error = line.split(' ')
				else:
					qe, num_iter, error = line.split(' ')

				if num_iter == 'secs:':
					tiempo_ejecucion = error
				else:
					data[int(num_iter)] =  float(error)

			i += 1
		f.close()
		yield data

if __name__ == '__main__':
	plotearPropagacionDelError()