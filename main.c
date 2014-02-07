#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "uiFunctions.h"
#include "dataFunctions.h"

int main(void)
{
	readIn();
	initscr();
	int dump = 0;
	int toggle = 1;
	while(toggle)
	{
		ncursesOutput();
		char input = getch();
		
		switch(input)
		{
			case 'q': 
				toggle = 0; break;
			
			case 'a':
				nAddEntry(); break;
			
			case 'd':
				dump = 1; break;
			default: 
				toggle = 0; break;
		}
	}
	writeOut();
	endwin();
	if(dump) smallOutput();
	return EXIT_SUCCESS;
}
