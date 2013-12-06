#Variable: span
#Fijos: h, c_i
h = 4
carga = 250
min_span = 1
max_span = 100
min_n = 1
max_n = 41
C = 100000
fmax = 100000

f = open('medicionesConSpanVariable.in', 'w')
for span in range(min_span, max_span):
	for n in filter(lambda n: n%2 == 0, range(min_n, max_n)):
		f.write(str(span)+'\n')
		f.write(str(h)+'\n')
		f.write(str(n)+'\n')
		for i in range(n-1):
                        f.write(str(carga)+'\n')
		f.write(str(C)+'\n')
		f.write(str(fmax)+'\n')
		f.write('\n')
f.truncate(f.tell()-2)
f.close()



#Variable: c_i
#Fijos: span, h	
span = 50
h = 4
min_carga = 1
max_carga = 1000
min_n = 1
max_n = 41
C = 100000
fmax = 100000

f = open('medicionesConCargaVariable.in', 'w')
for carga in filter(lambda n: n%10 == 0, range(min_carga, max_carga+1)):
	for n in filter(lambda n: n%2 == 0, range(min_n, max_n)):
		f.write(str(span)+'\n')
		f.write(str(h)+'\n')
		f.write(str(n)+'\n')
		for i in range(n-1):
                        f.write(str(carga)+'\n')
		f.write(str(C)+'\n')
		f.write(str(fmax)+'\n')
		f.write('\n')
f.truncate(f.tell()-2)
f.close()


