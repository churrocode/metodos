CC=gcc
CFLAGS=-g -O0 -D=MEDIR
LDFLAGS=-g
OBJS=metodos.o
OBJS_PRUEBAS=pruebas.o
OBJS_MEDICIONES=mediciones.o
SOURCES=$(OBJS:.o=.c) *.h

mediciones: $(OBJS) $(OBJS_MEDICIONES)
	$(CC) $(LDFLAGS)  $(OBJS) $(OBJS_MEDICIONES) -o $@

pruebas: $(OBJS) $(OBJS_PRUEBAS)
	$(CC) $(LDFLAGS)  $(OBJS) $(OBJS_PRUEBAS) -o $@

%.o: %.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f ./*.o
	rm -f dependiente
