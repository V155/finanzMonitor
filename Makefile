finanzMonitor	:	main.o

main.o	:	main.c
		cc -Wall main.c -l ncurses
