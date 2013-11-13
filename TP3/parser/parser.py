import matplotlib.pyplot as pplot

eps = 1.0e-15

def plotearPropagacionDelError():
	labels = ['c = 0.5', 'c = 0.2', 'c = 0.8']
	lista_archivos = ['mediciones.out', 'mediciones2.out', 'mediciones3.out']
	i = 0
	for data in  parsearPropagacionDelError(lista_archivos):
		pplot.plot(data.keys(), data.values(), label=labels[i])
		i += 1
	pplot.axhline(eps, linestyle='--', label='Epsilon = 1.0e-15', c='g')
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
				num_iter, error = line.split(' ')
				data[int(num_iter)] =  float(error)
			i += 1
		f.close()
		yield data

if __name__ == '__main__':
	plotearPropagacionDelError()