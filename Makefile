CFLAGS=-Wall
LDFLAGS=-lncursesw

finanzMonitor : 
	${CC} ${CFLAGS} -o $@ $< ${LDFLAGS}

clean :
	rm finanzMonitor
