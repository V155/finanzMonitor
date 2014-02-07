CFLAGS=-Wall
LDFLAGS=-lncursesw

finanzMonitor : dataFunctions.o uiFunctions.o
	${CC} ${CFLAGS} -o $@ $< ${LDFLAGS}

clean :
	rm finanzMonitor

dataFunctions.o :
	${CC} ${CFLAGS} -c dataFunctions.c

uiFunctions.o :
	${CC} ${CFLAGS} -c uiFunctions.c ${LDFLAGS}
