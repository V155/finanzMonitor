#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#define ROWLENGTH 46

//the struct that represents one entry
struct entry
{
	//a char to store the category
	char category[8];
	//a char to store the description
	char desc[16];
	//an int to store the price in cents
	int price;
	//an int to store the date without the dots in format ddMMYYYY
	int date;
};

struct fixcost
{
	//a char to store the description
	char desc[16];
	//an int to store the price in cents
	int price;
};

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
//an char array that stores the userinput
char buf[16];
//int containing the sum of the entries with category==KAT1
int sum1 = 0;
//stores the sums of the categories
int sums[16];
//stores the names of the categories
char knCats[16][8];
//stores the number of found categories
int numCat = 0;

int readIn(void);
void smallOutput(void);
void ncursesOutput(void);
void drawLine(int length);
int calcSums(void);
int writeOut(void);
int checkKnown(char cat[8]);
void drawSpecialCharacter(char specialCharacter);
void drawTableSeperatorLine(char specialCharacter);
void nAddEntry();
void createEntry(char category[8], char desc[16], int price, int date);

WINDOW *create_newwin(int height, int width ,int starty, int startx);
void destroy_win(WINDOW *local_win);


int main(void)
{
	readIn();
	//smallOutput();
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
	//nAddEntry();
	//ncursesOutput();
	//calcSums();
	
	writeOut();
	
	endwin();

	if(dump) smallOutput();

	return EXIT_SUCCESS;
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

void smallOutput()
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

void createEntry(char category[8], char desc[16], int price, int date)
{
	strcpy(entries[entriesIndex].category, category);
	strcpy(entries[entriesIndex].desc, desc);
	entries[entriesIndex].price = price;
	entries[entriesIndex].date = date;
	entriesIndex++;
	writeOut();
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

//reads the data from the save.csv
int readIn(void)
{
	//pointer to the savefile
	FILE *savefile;
	FILE *incomesfile;
	FILE *billsfile;
	//char array that contains the read data
	char puffer[ROWLENGTH];
	//the name of the savefile
	char name[] = {"save.csv"};
	char name2[] = {"incomes.csv"};
	char name3[] = {"bills.csv"};
	
	//incomes file is opened read-only
	incomesfile = fopen(name2, "r");
	if(incomesfile == NULL)
	{
		printf("No incomes.csv file found skipping");
	} else
	{
		char *ptr;
		while ( fgets(puffer, ROWLENGTH, incomesfile) != NULL)
		{
			ptr = strtok(puffer, ",");
			
			if(ptr != NULL)
				strcpy(incomes[incomesIndex].desc, ptr);
			ptr = strtok(NULL, ",");
			if(ptr != NULL)
				incomes[incomesIndex].price = atoi(ptr);
			
			incomesIndex ++;
			
		}
	}
	fclose(incomesfile);
	//bills file is opened read-only
	billsfile = fopen(name3, "r");
	if(billsfile == NULL)
	{
		printf("No bills.csv file found skipping");
	} else
	{
		char *ptr;
		while ( fgets(puffer, ROWLENGTH, billsfile) != NULL)
		{
			ptr = strtok(puffer, ",");
			
			if(ptr != NULL)
				strcpy(bills[billsIndex].desc, ptr);
			ptr = strtok(NULL, ",");
			if(ptr != NULL)
				bills[billsIndex].price = atoi(ptr);
			
			billsIndex ++;
			
		}
	}
	fclose(billsfile);
	//savefile is opened read-only
	savefile = fopen (name, "r");
	if (savefile == NULL){
		//checks if file can be opened
		perror ("Error opening file");
		return 1;
	}
	else {
		//pointer to store the fields of the csv in
		char *ptr;
		if ( fgets (puffer, ROWLENGTH , savefile) != NULL)
		{
			//read all lines of file
			while ( fgets (puffer , ROWLENGTH , savefile) != NULL )
			{
				//expected file format: category,shortdescription,priceInCent,date
				//read in the first field
				ptr = strtok(puffer, ",");
				// check if there was a field
				if (ptr != NULL)
					strcpy(entries[entriesIndex].category , ptr);//write the content of the read field into the struct
				ptr = strtok(NULL, ",");
				if (ptr != NULL)
					strcpy(entries[entriesIndex].desc, ptr);
				ptr = strtok(NULL, ",");
				if (ptr != NULL)
					entries[entriesIndex].price = atoi(ptr);
				ptr = strtok(NULL, ",");
				if (ptr != NULL)
					entries[entriesIndex].date = atoi(ptr);
				
				entriesIndex ++;
			}
		}
	}
	
	fclose (savefile);
	
	return 0;
}

int writeOut(void)
{
	int i=0;
	//pointer to the savefile
	FILE *savefile;
//    char puffer[ROWLENGTH]; //char array that contains the read data
	//the name of the savefile
	char name[] = {"save.csv"};
	
	savefile=fopen(name,"w");
	if(savefile == NULL){
		perror ("Error opening file for writing");
		return 1;
	}
	else{
		
		fprintf(savefile, "Category, Desctiption, Price in cent, Date\n");
		for(i=0; i < entriesIndex; i++){
			
			//sprintf(puffer,"%s,%s,%d,%d\n",entries[i].category, entries[i].desc, entries[i].price, entries[i].date);
			fprintf(savefile,"%s,%s,%d,%d\n",entries[i].category, entries[i].desc, entries[i].price, entries[i].date);
			//fputs(puffer,savefile);
		}
	}
	
	fclose(savefile);
	
	return 0;
	
}

//calculates the Sum of expenses for each category
int calcSums(void)
{
	//first clear sums array
	int z = numCat;
	for(; z > -1; z-- )
	{
		sums[z] = 0;
	}
	//needed for the known category check
	int eq = 0;
	int i = 0;
	for(i=0; i < entriesIndex; i++){
		//returns index of category in knCats array if known. else -1
		eq = checkKnown(entries[i].category);
		
		if(eq == -1){
			//append the category to the known categories array
			strcpy(knCats[numCat], entries[i].category);
			sums[numCat] = entries[i].price;
			numCat++;
		}
		else{
			//increase the sum by the price of the actual entry
			sums[eq] = sums[eq] + entries[i].price;
		}
	}
	
	
	//for (i = 0 ; i < numCat; i++){
	//	printf("Sum of %s is : %d\n", knCats[i], sums[i]);
	//	sum1 += sums[i];
	//}
	//printf("Overall Sum: %d\n", sum1);
	
	return 0;
}

int checkKnown(char cat[8]){
	
	//stores 0 if equal and 1 if not
	int e = 0;
	//var for the second loop
	int k = 0;
	int i = 0;
	
	for (i = 0; i < numCat; i++){
		e=0;
		for (k = 0; k < 8; k++){
			if (knCats[i][k] != cat[k]){
				e = 1;
				break;
			}
		}
		if (e == 0){
			return i;
		}
	}
	return -1;
}
