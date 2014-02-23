#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "uiFunctions.h"
#include "dataFunctions.h"
/**
//an array with length 100 to store the entries for at least a month
struct entry entries[100];
//an array with length 50 to store the fix incomes
struct fixcost incomes[50];
//an array with length 50 to store the fix costs
struct fixcost bills[50];
//the actual index while accessing the entries array
int entriesIndex = 0;
//the actual index while accessing the incomes array
int incomesIndex = 0;
//the actual index while accessing the bills array
int billsIndex = 0;
//int containing the sum of the entries with category==KAT1
int sum1 = 0;
//stores the sums of the categories
int sums[16];
//stores the names of the categories
char knCats[16][8];
//stores the number of found categories
int numCat = 0;
*/
struct month month;


int main(void)
{
//	readIn(&incomesIndex, incomes, &billsIndex, bills, &entriesIndex, entries);
	readIn(month);
	initscr();
	int dump = 0;
	int toggle = 1;
	while(toggle)
	{
		ncursesOutput(month.incomesIndex, month.incomes, month.billsIndex, month.bills, month.entriesIndex, month.entries, month.sum1, month.numCat, month.knCats, month.sums);
		char input = getch();
		
		switch(input)
		{
			case 'q': 
				toggle = 0; break;
			
			case 'a':
				nAddEntry(&month.entriesIndex, month.entries); break;
			
			case 'd':
				dump = 1; break;
			default: 
				toggle = 0; break;
		}
	}
	writeOut(month.entriesIndex, month.entries);
	endwin();
	if(dump) smallOutput(month.incomesIndex, month.incomes, month.billsIndex, month.bills, month.entriesIndex, month.entries,  month.numCat, month.knCats, month.sums, month.sum1);
	return EXIT_SUCCESS;
}
