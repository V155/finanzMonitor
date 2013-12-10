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

//an array with length 100 to store the entries for at least a month
struct entry entries[100];
//the actual index while accessing the entries array
int actIndex = 0;
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
WINDOW *create_newwin(int height, int width ,int starty, int startx);
void destroy_win(WINDOW *local_win);


int main(void)
{
	readIn();
	//smallOutput();
	initscr();
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
			
			default: 
				toggle = 0; break;
		}
	}
	//nAddEntry();
	//ncursesOutput();
	//calcSums();
	writeOut();
	
	endwin();
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
	strcpy(entries[actIndex].category , category);
	strcpy(entries[actIndex].desc, desc);
	entries[actIndex].price = price;
	entries[actIndex].date = date;
	
	actIndex++;
	
	return 0;
	
}

void smallOutput(void)
{
	//just an int to iterate over the array of structs
	int i = 0;
	
	printf("*------+----------+------------------+----------+----------*\n");
	printf("* Nr   | Category | Description      | Price    | Date     *\n");
	printf("*------+----------+------------------+----------+----------*\n");
	
	for(i=0; i< actIndex; i++){
		printf("* %4d | %8s | %16s | %8d | %8d *\n", i, entries[i].category, entries[i].desc, entries[i].price, entries[i].date);
	}
	
	printf("*------+----------+------------------+----------+----------*\n");
}

int output(void)
{
	//just an int to iterate over the array of structs
	int i = 0;
	//an iteration over all the entries and output of them
	for(i=0; i < actIndex; i++)
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
	
	
	for(i=0; i< actIndex; i++){
		
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
	printw("Overall Sum: %d\n", sum1);
	
	
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
	
	strcpy(entries[actIndex].category, category);
	strcpy(entries[actIndex].desc, desc);
	entries[actIndex].price = price;
	entries[actIndex].date = date;
	actIndex++;
	
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

//reads the data from the save.csv
int readIn(void)
{
	//pointer to the savefile
	FILE *savefile;
	//char array that contains the read data
	char puffer[ROWLENGTH];
	//the name of the savefile
	char name[] = {"save.csv"};
	
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
		//read all lines of file
		while ( fgets (puffer , ROWLENGTH , savefile) != NULL ){
			
			//expected file format: category,shortdescription,priceInCent,date
			//read in the first field
			ptr = strtok(puffer, ",");
			// check if there was a field
			if (ptr != NULL)
			strcpy(entries[actIndex].category , ptr);//write the content of the read field into the struct
			ptr = strtok(NULL, ",");
			if (ptr != NULL)
			strcpy(entries[actIndex].desc, ptr);
			ptr = strtok(NULL, ",");
			if (ptr != NULL)
			entries[actIndex].price = atoi(ptr);
			ptr = strtok(NULL, ",");
			if (ptr != NULL)
			entries[actIndex].date = atoi(ptr);
			
			actIndex ++;
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
		for(i=0; i < actIndex; i++){
			
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
	for(i=0; i < actIndex; i++){
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
