#coding: utf-8
import matplotlib as mpl
import re
import sys
from math import log

if sys.platform == 'darwin': 
	mpl.use('cocoaagg')		#hack para mac
import matplotlib.pyplot as pplot

from matplotlib.font_manager import FontProperties

fontP = FontProperties()
fontP.set_size('small')


# ordenes = [0.000000001, 0.000001, 0.001, 0.1, 1, 10, 1000, 1000000, 1000000000]
ordenes = {0 : 0.000000001, 1: 0.000001, 2: 0.001, 3: 0.1, 4: 1, 5: 10, 6 : 1000, 7 :1000000, 8: 1000000000};
tolerancias = ['10^-18', '10^-15', '10^-12', '10^-9', '10^-6', '10^-3']
nombresMetodos = [r"Newton para $x^2$ - $\alpha$", r'Newton para $1/x^2 - \alpha$', r"Punto fijo para $1/x^2 - \alpha$", "Biseccion"]



def main():
	data_span = parsearYPromediarSpanVariable()
	data_carga = parsearYPromediarCargaVariable()
	title_span = 'Span variable con carga fija (promediando secciones)'
	title_carga = 'Carga variable (uniforme) con span fijo (promediando secciones)'
	plotBars(data=data_span.values(),labels=range(len(data_span)),title=title_span, xlabel='Span',ylabel=u'Fuerza máxima ejercida').show()
	plotBars(data=data_carga.values(),labels=range(len(data_carga)),title=title_carga,xlabel='Carga', ylabel=u'Fuerza máxima ejercida').show()


def plotBars(data, labels, title = None, horizontalLine = None, widthLevel = 1, verticalLine = None, offset = 0.5, color = 'b', xlabel = None, ylabel = None):
	import numpy.numarray as na
	xlocations = na.array(range(len(data)/widthLevel)) + offset
	width = 0.5 * widthLevel
	pplot.bar(xlocations, data, width=width, color = color)
	pplot.xticks(xlocations+0.5*width, labels, fontsize = 12) #, rotation = 30
	pplot.xlim(0, xlocations[-1]+width*2)
	if title:
		pplot.title(title)
	if horizontalLine:
		pplot.axhline(linewidth=2, color='r', y = horizontalLine) 
	if verticalLine:
		pplot.axvline(linewidth=2, color='r', x = verticalLine) 
	if xlabel:
		pplot.xlabel(xlabel)
	if ylabel:
		pplot.ylabel(ylabel)
	pplot.gca().get_xaxis().tick_bottom()
	pplot.gca().get_yaxis().tick_left()
	return pplot

def plotearDiciembre(dataGenerator, drawLine = False):
	data = dataGenerator()
	for n in data.iterkeys():
		x = map(lambda t: t[0], data[n])
		y = map(lambda t: t[1], data[n])
		if drawLine:
			pplot.plot(x, y, marker='.', linestyle ='-')
			pplot.text(x[0], y[0], 'n = ' + str(n))
		else:
			pplot.plot(x, y, '.')
			pplot.text(x[-5], y[-1], 'n = ' + str(n))
	#pplot.legend()

def plotearCargaDiciembre():
	pplot.figure()
	plotearDiciembre(parsearCargaVariableDiciembre)
	pplot.title(u'Fuerza máxima observada para distintos valores de carga uniforme y de secciones (n), con span = 50m')
	pplot.xlabel(u'Carga en cada junta inferior [N]')
	pplot.ylabel(u'Fuerza máxima observada sobre algún link [N]')
	pplot.show()

def plotearSpanDiciembre():
	pplot.figure()
	plotearDiciembre(parsearSpanVariableDiciembre)
	pplot.title(u'Fuerza máxima observada para distintos valores de span y de secciones (n), con carga uniforme de 250 N')
	pplot.xlabel(u'Span [m]')
	pplot.ylabel(u'Fuerza máxima observada sobre algún link [N]')
	pplot.show()

def plotearSpanDiciembreDetalle():
	pplot.figure()
	plotearDiciembre(parsearSpanVariableDiciembreDetalle, drawLine = True)
	pplot.title(u'Fuerza máxima observada para distintos valores de span y de secciones (n), con carga uniforme de 250 N')
	pplot.xlabel(u'Span [m]')
	pplot.ylabel(u'Fuerza máxima observada sobre algún link [N]')
	pplot.show()	

def parsearCargaVariableDiciembre():
	return parsearSalidaDiciembre('medicionesConCargaVariable.out')

def parsearSpanVariableDiciembre():
	return parsearSalidaDiciembre('medicionesConSpanVariable.out')

def parsearSpanVariableDiciembreDetalle():
	data = parsearSpanVariableDiciembre()
	for n in data.iterkeys():
		data[n] = filter(lambda t: t[0] <= 20, data[n])
	return data
	
def parsearSalidaDiciembre(fileName):
	f = open(fileName, 'r')
	data = {}
	map(lambda l: parsearLineaDe3(l, data), f) #te quiero, python
	#data[n] = [(var_i, F_i)] -> para cada n medido, data[n] tiene tuplas (var, F): FMax observada para cada var medido.
	return data

def parsearLineaDe3(linea, data):
	linea = linea.split()
	if len(linea):
		print linea
		# linea = [carga/span, n, FMax]
		var = int(linea[0]) #carga o span, segun corresponda
		n = int(linea[1])
		F = float(linea[2])
		if data.has_key(n):
			data[n].append((var, F))
		else:
			data[n] = [(var, F)] 
	#data[n] = [(var_i, F_i)] -> para cada n medido, data[n] tiene tuplas (var, F): FMax observada para c/ var medido.



def parsearYPromediarCargaVariable():
	f = open('medicionesConCargaVariable.out', 'r')
	data = {}
	i = 0
	ultimaCarga = None
	cant_sumas = 1
	for line in f:
		if not line == '\n':
			if line[-1] == '\n':
				line = line[:-1]
			if i % 3 == 0: #CONTIENE LA CARGA 
				if ultimaCarga != int(line):
					ultimaCarga = int(line)
					data[int(ultimaCarga)] = 0
					cant_sumas = 1
				else:
					cant_sumas += 1
			elif i % 3 == 1: #CONTIENE EL N
				pass
			elif i % 3 == 2:
				data[int(ultimaCarga)] += float(line)  
			i += 1
	for key, sig in data.iteritems():
		data[key] = data[key] / cant_sumas
	return data



def parsearYPromediarSpanVariable():
	f = open('medicionesConSpanVariable.out', 'r')
	data = {}
	i = 0
	ultimoSpan = None
	cant_sumas = 1
	for line in f:
		if not line == '\n':
			if line[-1] == '\n':
				line = line[:-1]
			if i % 3 == 0: #CONTIENE EL SPAN 
				if ultimoSpan != int(line):
					ultimoSpan = int(line)
					data[int(ultimoSpan)] = 0
					cant_sumas = 1
				else:
					cant_sumas += 1
			elif i % 3 == 1: #CONTIENE EL N
				pass
			elif i % 3 == 2:
				data[int(ultimoSpan)] += float(line)  
			i += 1
	for key, sig in data.iteritems():
		data[key] = data[key] / cant_sumas
	return data






def definirIntervalo(x):
	for o in ordenes:
		if x <= 5*o:
			return o

def parsearYProbar():
	f = open('buscarParadaMetodo0.dat', 'r')
	data = {}
	for l in f:
		if len(l) and l[0] != '#' and l[0] != '*':
			sL = l.split(':')
			if sL[0] in data.keys():
				data[sL[0]].append(sL[4])
			else:
				data[sL[0]] = [sL[4]]
	return data

def parsearYPromediar(fileDesc):
	tolerancia = 0
	data = []
	dataFinal = {}
	for l in fileDesc:
		if len(l)> 0 and l[0] != '#':
			if l[0] == '*':
				m = re.search('10..(\d+)', l)
				if m:
					tolerancia = m.group(0)
					dataFinal[tolerancia] = cerrarPromedio(data)
					data=[]
			else:
				valores = map(lambda s: float(s), l.split(':'))
				data.append((int(valores[0]), valores[1], abs(valores[4])))
	#dataFinal[tolerancia] = {orden : errorPromedio}
	return dataFinal

prom = lambda l : sum(l)/len(l) if len(l) else 0
	

def cerrarPromedio(data):
	dataSeparada = {o : [] for o in ordenes.keys()}
	for (orden, alpha, error) in data:
		dataSeparada[orden].append(error)
	return {k : (prom(l)) for k,l in dataSeparada.items()}

def separarData(dataYLabels):
	data = []
	labels = []
	for (label, datum) in dataYLabels:
		data.append(datum)
		labels.append(label)
	return data, labels

def parsearYPromediarTiempos(fileDesc):
	data = []
	dataFinal = {}
	for l in fileDesc:
		if len(l)> 0 and l[0] != '#':
			valores = map(lambda s: float(s), l.split(':'))
			data.append(valores)
	for lista in data:
		if not lista[0] in dataFinal:
			dataFinal[lista[0]] = lista[2]
		else:
			dataFinal[lista[0]] += lista[2]
	for orden in dataFinal:
		dataFinal[orden] = dataFinal[orden] / 42
	return dataFinal



def parseTiempos(fileDesc):
	tams = []
	thruput = []
	timeOuts = []
	# for line in fileDesc:
	# 	line = line.split()
	# 	if !len(line) or line[0][0] == '#':
	# 		continue
	# 	tams.append(int(line[1]))
	# 	thruput.append(float(line[3]))
	# 	timeOuts.append(float(line[5]))
	parse(fileDesc, [(tams, 1, int),(thruput,3,float),(timeOuts, 5, float)])
	return tams, thruput, timeOuts

def parseVentanas(fileDesc):
	ventanas = []
	fruput = []
	timeouts = []
	parse(fileDesc, [(ventanas, 1, int), (fruput, 3, float), (timeouts, 5, float)])
	return ventanas, fruput, timeouts


def parse(fileDesc, mapListaIndiceFormat):
	for line in fileDesc:
		line = line.split()
		if (not len(line)) or line[0][0] == '#':
			continue
		for lista, indice, format in mapListaIndiceFormat:
			lista.append(format(line[indice]))


def barrasDeThroughput(filename):
	pplot.figure()
	data = open(filename, 'r')
	tams, fruput, l = parseTiempos(data)
	data.close()
	plotBars(fruput, tams, u'Throughput percibido para envíos de distinto tamaño')
	pplot.xlabel(u'Tamaño del mensaje [B]')
	pplot.ylabel(u'Throughput percibido [B/s]')
	pplot.show()

def barrasDeVentanas(filename, extraString=''):
	pplot.figure()
	data = open(filename, 'r')
	ventanas, fruput, timeouts = parseVentanas(data)
	data.close()
	plotBars(fruput, ventanas, u'Throughput percibido para distintos tamaños de ventana ' + extraString)
	pplot.xlabel(u'Tamaño de vantena [Paquetes]')
	pplot.ylabel(u'Throughput percibido [B/s]')
	pplot.show()

#print data


def plotNBars(data,labels, title = None, numeroMetodo = None, horizontalLine = None, verticalLine = None):
	global ordenes
	global tolerancias
	global fontP

	print data
	print labels

	import numpy.numarray as na
	xlocations = na.array(range(len(data[0])))
	width = 0.7
	i = 0
	colores = ['b','g','r','c','m','y','k','w','#610b0b']
	bar_width = float(width/len(data))
	print bar_width
	bars = []
	for dataOrden in data:
		bars.append(pplot.bar(xlocations+bar_width*i, dataOrden, bar_width, color = colores[i]))
		i += 1
	pplot.xlabel(r'Orden de magnitud para $\alpha$')
	pplot.ylabel(r'Tiempo en $\mu$s')
	if title:
		pplot.title(title)
	if horizontalLine:
		hline = pplot.axhline(linewidth=2, color='r', y = horizontalLine, linestyle='dashed', label = 'Epsilon para igualdad') 
		bars.append(hline)
	if verticalLine:
		pplot.axvline(linewidth=2, color='r', x = verticalLine) 
	#ordenes_legends = ['Orden de magnitud: {}'.format(ordenes[x]) for x in range(len(ordenes))]
	#ordenes_legends.append('Epsilon para igualdad: {}'.format(horizontalLine))
	#pplot.legend( bars, ordenes_legends, loc='best', prop = fontP)
	pplot.xticks(xlocations+width/2, map(lambda x: log(x,10), ordenes.values()), fontsize = 12) #, rotation = 30
	pplot.savefig('Tiempo metodo {}.png'.format(numeroMetodo))
	#pplot.show()


def plot2Bars(data1, data2, data3, labels, title = None, horizontalLine = None, verticalLine = None):
	import numpy.numarray as na
	xlocations = na.array(range(len(data1)))
	width = 0.35
	bars1 = pplot.bar(xlocations, data1, width=width, color = 'b')
	bars2 = pplot.bar(xlocations+width, data2, width=width, color = 'g')
	pplot.xlabel(u'Tamaño de vantena [Paquetes]')
	pplot.ylabel(u'Throughput percibido [B/s]')
	pplot.title(u'Throughput percibido para distintos tamaños de ventana')
	# pplot.xlim(0, xlocations[-1]+width*2)
	if title:
		pplot.title(title)
	if horizontalLine:
		pplot.axhline(linewidth=2, color='r', y = horizontalLine, linestyle='dashed') 
	if verticalLine:
		pplot.axvline(linewidth=2, color='r', x = verticalLine) 
	pplot.gca().get_xaxis().tick_bottom()
	pplot.gca().get_yaxis().tick_left()
	ax2 = pplot.twinx()
	dots = ax2.plot(xlocations + width, data3, 'ro')
	pplot.legend( (bars1[0], bars2[0], dots[0]), (u'sin pérdidas', u'con pérdidas', u'timeouts por transmisión'), ncol = 3 )
	ax2.set_ylabel(u'Timeouts promedio por transmisión (con pérdidas)')
	ax2.set_ylim([0, max(map(lambda t: int(t), data3)) + 3])
	pplot.gca().get_yaxis().tick_right()
	pplot.xticks(xlocations+width, labels, fontsize = 12) #, rotation = 30

def barrasDeVentanas2(filenameSinC, filenameConC):
	pplot.figure()
	dataSinC = open(filenameSinC, 'r')
	dataConC = open(filenameConC, 'r')
	ventanasSinC, fruputSinC, timeoutsSinC = parseVentanas(dataSinC)
	ventanasConC, fruputConC, timeoutsConC = parseVentanas(dataConC)
	print 'con', ventanasConC, fruputConC, timeoutsConC
	print 'sin', ventanasSinC, fruputSinC, timeoutsSinC
	dataSinC.close()
	dataConC.close()	
	plot2Bars(data1 = fruputSinC, data2 = fruputConC, data3 = timeoutsConC, labels = ventanasSinC)
	#plotBars(data = fruputSinC, labels = ventanasSinC, title= u'Throughput percibido para distintos tamaños de ventana', widthLevel = 1, offset = 0 )
	# plotBars(data = fruputConC, labels = ventanasConC , widthLevel = 2, offset = 0.5, color = 'r')
	pplot.show()


def barrasYRedondos(filename, filenameRedondo):
	pplot.figure()
	data = open(filename, 'r')
	dataR = open(filenameRedondo, 'r')
	tams, fruput, l = parseTiempos(data)
	tamsR, fruputR, l = parseTiempos(dataR)
	data.close()
	dataR.close()
	import numpy.numarray as na
	xlocations = na.array(range(len(fruput)))
	width = 0.5
	pplot.gca().get_xaxis().tick_bottom()
	pplot.gca().get_yaxis().tick_left()
	xlocations2 = xlocations[0:len(fruputR)]
	bars2 = pplot.bar(xlocations2+0.75, fruputR, 0.25, color = '0.5')
	pplot.bar(xlocations+0.25, fruput, width=width, color = 'g')
	pplot.xticks(xlocations+0.5, tams, fontsize = 12) #, rotation = 30
	pplot.xlabel(u'Tamaño del mensaje [B]')
	pplot.ylabel(u'Throughput percibido [B/s]')
	pplot.title(u'Throughput percibido para envíos de distinto tamaño')
	pplot.show()




# N = len(data)
# menMeans = (20, 35, 30, 35, 27)
# menStd =   (2, 3, 4, 1, 2)

# ind = np.arange(N)  # the x locations for the groups
# width = 0.35       # the width of the bars


# plt.subplot(111)
# rects1 = plt.bar(ind, menMeans, width,
#                     color='r',
#                     yerr=menStd,
#                     error_kw=dict(elinewidth=6, ecolor='pink'))

# womenMeans = (25, 32, 34, 20, 25)
# womenStd =   (3, 5, 2, 3, 3)
# rects2 = plt.bar(ind+width, womenMeans, width,
#                     color='y',
#                     yerr=womenStd,
#                     error_kw=dict(elinewidth=6, ecolor='yellow'))

# # add some
# plt.ylabel('Scores')
# plt.title('Scores by group and gender')
# plt.xticks(ind+width, ('G1', 'G2', 'G3', 'G4', 'G5') )

# plt.legend( (rects1[0], rects2[0]), ('Men', 'Women') )

if __name__ == '__main__':
	main()

	'''	
	for i in range(4):
		print i
		data = parsearYPromediarTiempos(open('medirTiemposParaMetodo{}.dat'.format(i), 'r'))
		plotNBars([data.values()],labels=range(len(data)) , title='Tiempo de ejecucion {}'.format(nombresMetodos[i]), numeroMetodo = i)
		pplot.cla()


	eps = 1e-15
	for i in range(4):
		data = parsearYPromediar(open('buscarParadaMetodo{}.dat'.format(i), 'r'))
		dataOrdenes = []
		for orden in range(len(ordenes)):
			dataOrden = [data[x][orden] for x in tolerancias]
			dataOrdenes.append(dataOrden)
		print len(dataOrdenes)
		plotNBars(dataOrdenes,tolerancias,horizontalLine=eps,title='metodo{}'.format(i))
		pplot.cla()
	'''


