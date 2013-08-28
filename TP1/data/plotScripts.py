#coding: utf-8
import matplotlib as mpl
import re
mpl.use('cocoaagg')		#hack para mac
import matplotlib.pyplot as pplot

ordenes = [0.000000001, 0.000001, 0.001, 0.1, 1, 10, 1000, 1000000, 1000000000]
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
	orden = 0
	data = []
	dataFinal = {}
	for l in fileDesc:
		if len(l)> 0 and l[0] != '#':
			if l[0] == '*':
				m = re.search('10..(\d+)', l)
				if m:
					orden = m.group(0)
					print orden
					dataFinal[orden] = cerrarPromedio(data)
					data=[]
			else:
				valores = map(lambda s: float(s), l.split(':'))
				data.append((valores[0], abs(valores[4])))
	return dataFinal

def cerrarPromedio(data):
	dataSeparada = {str(o) : [] for o in ordenes}
	for (alpha, error) in data:
		dataSeparada[str(definirIntervalo(alpha))].append(error)
	return {k : (sum(l)/len(l) if len(l) else 0) for k,l in dataSeparada.items()}

def separarData(dataYLabels):
	data = []
	labels = []
	for (label, datum) in dataYLabels:
		data.append(datum)
		labels.append(label)
	return data, labels

def plotBars(data, labels, title = None, horizontalLine = None, widthLevel = 1, verticalLine = None, offset = 0.5, color = 'g'):
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
	pplot.gca().get_xaxis().tick_bottom()
	pplot.gca().get_yaxis().tick_left()
	return pplot

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
		pplot.axhline(linewidth=2, color='r', y = horizontalLine) 
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




