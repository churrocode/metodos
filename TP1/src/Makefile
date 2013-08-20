CC=gcc
CFLAGS=-g -O0
LDFLAGS=-g
OBJS=metodos.o
OBJS_PRUEBAS=pruebas.o
SOURCES=$(OBJS:.o=.c) *.h

pruebas: $(OBJS) $(OBJS_PRUEBAS)
	$(CC) $(LDFLAGS)  $(OBJS) $(OBJS_PRUEBAS) -o $@

%.o: %.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f ./*.o
	rm -f dependiente
