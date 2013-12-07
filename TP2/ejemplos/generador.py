"""Para generar archivos de prueba para la competencia"""
#Formato span \n h \n c_1 \n c_2 \n ... \n c_n-1 \n costoPilar \n FMax \n
import sys

def generarCargas(openFile, n, distr, q1, q2 = None):
	if distr == 'U':
		for i in range(n-1):
			openFile.write("{0}\n".format(q1))
	elif distr == 'R':
		from random import uniform
		for i in range(n-1):
			openFile.write("{0}\n".format(uniform(q1, q2)))


if len(sys.argv) < 9 or (sys.argv[7] != 'R' and sys.argv[7] != 'U'):
	print "Se esperan los siguientes par'ametros (en este orden):"
	print "span h n costoPilar FMax outputFile distribucionDeCargas q1 [q2]"
	print "donde distribucionDeCargas puede ser U -> uniforme, y q1 es el valor"
	print "	      o R -> random, entre q1 y q2"
else:
	span = int(sys.argv[1])
	h = int(sys.argv[2])
	n = int(sys.argv[3])
	costoP = float(sys.argv[4])
	FMax = float(sys.argv[5])
	with open(sys.argv[6], 'w') as f:
		f.write("{0}\n{1}\n{2}\n".format(span, h, n))
		if sys.argv[7] == 'R':
			generarCargas(f, n, 'R', float(sys.argv[8]), float(sys.argv[9]))
		else:
			generarCargas(f, n, 'U', float(sys.argv[8]))
		f.write("{0}\n{1}".format(costoP, FMax))
	f.closed

