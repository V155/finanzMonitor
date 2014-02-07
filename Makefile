CFLAGS = -std=c99 -Wall ${CPPFLAGS}
#-Wextra -Werror -pedantic ${CPPFLAGS} 
LDFLAGS = -lncursesw

SRC=$(wildcard *.c)
OBJ=${SRC:.c=.o}
DEPS=${SRC:.c=.dep}

TARGET=finanzMonitor

all: ${TARGET}

%.dep: %.c
	$(CC) -MM $< -o $@

-include $(OBJ:%.o=%.dep)

${TARGET}: ${OBJ}
	${CC} -o $@ $^ ${LDFLAGS}

%.o: %.c %.dep
	${CC} -c ${CFLAGS} $<

clean: 
	${RM} ${OBJ}
	${RM} ${DEPS}

.PHONY: clean

