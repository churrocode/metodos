#Variable: span
#Fijos: h, c_i
h = 2
c = 1
min_span = 1
max_span = 5
min_n = 1
max_n = 5

f = open('medicionesConSpanVariable.txt', 'w')
for span in range(min_span, max_span):
	for n in range(min_n, max_n):
		if n % 2 == 0:
			f.write(str(span)+'\n')
			f.write(str(h)+'\n')
			f.write(str(n)+'\n')
			for c in range(n):
				f.write(str(c)+'\n')
			f.write('\n')
f.close()



#Variable: c_i
#Fijos: span, h
span = 10
h = 2
min_carga = 1
max_carga = 5
min_n = 1
max_n = 5

f = open('medicionesConCargaVariable.txt', 'w')
for carga in range(min_carga, max_carga):
	for n in range(min_n, max_n):
		if n % 2 == 0:
			f.write(str(span)+'\n')
			f.write(str(h)+'\n')
			f.write(str(n)+'\n')
			for c in range(n):
				f.write(str(carga)+'\n')
			f.write('\n')
f.close()


