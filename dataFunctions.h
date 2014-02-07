#ifndef _dataFunctions_H
#define _dataFunctions_H
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


void createEntry(int entriesIndex, struct entry* entries, char category[8], char desc[16], int price, int date);
int readIn(int incomesIndex, struct fixcost* incomes, int billsIndex, struct fixcost* bills, int entriesIndex, struct entry* entries);
int writeOut(int entriesIndex, struct entry* entries);
int calcSums(int entriesIndex, struct entry* entries, int numCat, int* sums, char** knCats);
int checkKnown(char cat[8], int numCat, char** knCats);
#endif /* _dataFunctions_H */
