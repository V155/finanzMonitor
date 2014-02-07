#include<ncurses.h>
#include "uiFunctions.h"
#include "dataFunctions.h"

//This function draws a horizontal line
void drawLine(int length)
{
	for(;length >= 0; length--){
		
		addch(ACS_HLINE);
		
	}
}

//this function prints a seperator line. @param specialCharacter is a char according to ncurses.h 
//that declares what specialCharacter should be used to display the first char of the line.
//The other needed specialCharacters are chosen accordingly.
void drawTableSeperatorLine(char specialCharacter)
{
	
	switch (specialCharacter){
		
		case 'v': addch(ACS_LLCORNER); break;
		case 'w': addch(ACS_ULCORNER); break;
		case 'n': addch(ACS_LTEE); break;
		default: break;
		
	}
	
	drawLine(5);
	drawSpecialCharacter(specialCharacter);
	drawLine(9);
	drawSpecialCharacter(specialCharacter);
	drawLine(17);
	drawSpecialCharacter(specialCharacter);
	drawLine(9);
	drawSpecialCharacter(specialCharacter);
	drawLine(9);
	
	switch (specialCharacter){
		
		case 'v': addch(ACS_LRCORNER); break;
		case 'w': addch(ACS_URCORNER); break;
		case 'n': addch(ACS_RTEE); break;
		default: break;
		
	}
}

void drawSpecialCharacter(char specialCharacter)
{
	switch (specialCharacter){
		
		case 't': addch(ACS_LTEE); break;
		case 'u': addch(ACS_RTEE); break;
		case 'v': addch(ACS_BTEE); break;
		case 'w': addch(ACS_TTEE); break;
		case 'n': addch(ACS_PLUS); break;
		default: break;
	}
}

void nAddEntry()
{
	char category[8];
	char desc[16];
	int price = 0;
	int date = 0;
	
	int height = 10;
	int width = 42;
	int starty = (LINES - height) / 2;
	int startx = (COLS - width) / 2;
	WINDOW *my_win = create_newwin(height, width, starty, startx);
	attron(A_BOLD);
	mvwprintw(my_win, 1, 2, "Adding new Entry");
	attroff(A_BOLD);
	mvwprintw(my_win, 3, 2, "Category         :");
	mvwprintw(my_win, 4, 2, "Description      :");
	mvwprintw(my_win, 5, 2, "Price in ct      :");
	mvwprintw(my_win, 6, 2, "Date in YYYYMMDD :");
	wrefresh(my_win);
	refresh();
	
	mvwgetnstr(my_win, 3, 22, category, 7);
	mvwgetnstr(my_win, 4, 22, desc, 15);
	mvwscanw(my_win, 5, 22, "%d", &price);
	mvwscanw(my_win, 6, 22, "%d", &date);

	int c;
	c = wgetch(my_win);
	switch(c)
	{
		case 10: createEntry(category, desc, price, date); break;
		default: break;
	}

	destroy_win(my_win);
	refresh();
}
WINDOW *create_newwin(int height, int width ,int starty, int startx)
{
	WINDOW *local_win;
	
	local_win = newwin(height, width, starty, startx);
	// creates border decoration with default line-draw-characters
	box(local_win, 0, 0);
	//show that box	
	wrefresh(local_win);
	
	return local_win;
}

void destroy_win(WINDOW *local_win)
{
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	wrefresh(local_win);
	delwin(local_win);
}

int input(void)
{
	char category[8];
	char desc[16];
	int price;
	int date;
	
	// just the whole input sequence here
	printf("Please enter Category : ");
	fgets(buf, 7, stdin);
	sscanf(buf, "%s", &category);
	memset(buf,'+',16);
	printf("Plese enter description : ");
	fgets(buf, 15, stdin);
	sscanf(buf, "%s", &desc);
	memset(buf, '\0',16);
	printf("Please enter price : ");
	fgets(buf, 8, stdin);
	sscanf(buf, "%d", &price);
	//memset(buf, '\0',strlen(buf));
	printf("Please enter date : ");
	fgets(buf, 9, stdin);
	sscanf(buf, "%d", &date);
	//memset(buf, '\0',strlen(buf));
	
	//copy the read values into the array of structs
	strcpy(entries[entriesIndex].category , category);
	strcpy(entries[entriesIndex].desc, desc);
	entries[entriesIndex].price = price;
	entries[entriesIndex].date = date;
	
	entriesIndex++;
	
	return 0;
	
}

void smallOutput(void)
{
	//just an int to iterate over the array of structs
	int i = 0;
	
	printf("*------+----------+------------------+----------+----------*\n");
	printf("* Nr   | Category | Description      | Price    | Date     *\n");
	printf("*------+----------+------------------+----------+----------*\n");

	for(i=0; i< incomesIndex; i++){
		printf("*      |          | %16s | %8d |          *\n", incomes[i].desc, incomes[i].price);
	}
	
	for(i=0; i< billsIndex; i++){
		printf("*      |          | %16s | %8d |          *\n", bills[i].desc, bills[i].price);
	}

	for(i=0; i< entriesIndex; i++){
		printf("* %4d | %8s | %16s | %8d | %8d *\n", i, entries[i].category, entries[i].desc, entries[i].price, entries[i].date);
	}
	
	printf("*------+----------+------------------+----------+----------*\n");
	
	for (i = 0 ; i < numCat; i++){
		printf("Sum of %s is : %d\n", knCats[i], sums[i]);
	}
	printf("Overall Sum: %d\n", sum1);

	int sumBills = 0;

	for (i=0; i < billsIndex; i++)
	{
		sumBills = sumBills + bills[i].price;
	}

	int sumIncomes = 0;

	for (i=0; i < incomesIndex; i++)
	{
		sumIncomes = sumIncomes + incomes[i].price;
	}

	int sumDiff; 
	sumDiff = sumIncomes - sumBills - sum1;
	
	printf("Saldo of Month is: %d\n", sumDiff);

}

int output(void)
{
	//just an int to iterate over the array of structs
	int i = 0;
	//an iteration over all the entries and output of them
	for(i=0; i < entriesIndex; i++)
	{
		printf ("*------------------------------------------*\n");
		printf ("* Nr:.................................%4d *\n", i);
		printf ("* Category:.......................%8s *\n", entries[i].category);
		printf ("* Description:............%16s *\n", entries[i].desc);
		printf ("* Price:..........................%8d *\n", entries[i].price);
		printf ("* Date:...........................%8d *\n", entries[i].date);
		printf ("*------------------------------------------*\n");
	}
	
	return 0;
}

void ncursesOutput(void){

	//start ncurses mode
	//initscr();
	move(0,0);
	//print the text
	//just an int to iterate over the array of structs
	int i = 0; 
	
	drawTableSeperatorLine('w');
	
	printw("\n");
	addch(ACS_VLINE);
	printw(" Nr   ");
	addch(ACS_VLINE);
	printw(" Category ");
	addch(ACS_VLINE);
	printw(" Description      ");
	addch(ACS_VLINE);
	printw(" Price    ");
	addch(ACS_VLINE);
	printw(" Date     ");
	addch(ACS_VLINE);
	printw("\n");
	
	drawTableSeperatorLine('n');
	printw("\n");
	
	for(i=0; i< incomesIndex; i++){
		
		addch(ACS_VLINE);
		printw(" %4s ", "x");
		addch(ACS_VLINE);
		printw(" %8s ", "x");
		addch(ACS_VLINE);
		printw(" %16s ", incomes[i].desc);
		addch(ACS_VLINE);
		printw(" %8d ", incomes[i].price);
		addch(ACS_VLINE);
		printw(" %8d ", 1);
		addch(ACS_VLINE);
		printw("\n");
	}

	for(i=0; i< billsIndex; i++){
		
		addch(ACS_VLINE);
		printw(" %4s ", "x");
		addch(ACS_VLINE);
		printw(" %8s ", "x");
		addch(ACS_VLINE);
		printw(" %16s ", bills[i].desc);
		addch(ACS_VLINE);
		printw(" %8d ", bills[i].price);
		addch(ACS_VLINE);
		printw(" %8d ", 1);
		addch(ACS_VLINE);
		printw("\n");
	}

	for(i=0; i< entriesIndex; i++){
		
		addch(ACS_VLINE);
		printw(" %4d ", i);
		addch(ACS_VLINE);
		printw(" %8s ", entries[i].category);
		addch(ACS_VLINE);
		printw(" %16s ", entries[i].desc);
		addch(ACS_VLINE);
		printw(" %8d ", entries[i].price);
		addch(ACS_VLINE);
		printw(" %8d ", entries[i].date);
		addch(ACS_VLINE);
		printw("\n");
	}
	



	
	drawTableSeperatorLine('v');
	printw("\n");
	
	calcSums();
	
	sum1 = 0;
	
	for (i = 0 ; i < numCat; i++){
		printw("Sum of %s is : %d\n", knCats[i], sums[i]);
		sum1 += sums[i];
	}

	int y;
	int x;
	y = 0;
	x = 0;

	getyx(stdscr, y, x);

	mvprintw(y-numCat, 30, "Overall Sum: %d\n", sum1);

	int sumBills = 0;

	for (i=0; i < billsIndex; i++)
	{
		sumBills = sumBills + bills[i].price;
	}

	int sumIncomes = 0;

	for (i=0; i < incomesIndex; i++)
	{
		sumIncomes = sumIncomes + incomes[i].price;
	}

	int sumDiff = 0;

	sumDiff = sumIncomes - sumBills - sum1;
	
	mvprintw(y-numCat+1, 30, "Saldo of Month is: %d\n", sumDiff);
	
	//refresh screen
	refresh();
	//end ncurses mode
	//endwin();
	
}
