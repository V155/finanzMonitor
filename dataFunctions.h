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


void createEntry(int* entI, struct entry* entries, char category[8], char desc[16], int price, int date);
int readIn(int* incI, struct fixcost* incomes, int* bilI, struct fixcost* bills, int* entI, struct entry* entries);
int writeOut(int entriesIndex, struct entry* entries);
int calcSums(int entriesIndex, struct entry* entries, int numCat, int* sums, char (*knCats)[8]);
int checkKnown(char cat[8], int numCat, char (*knCats)[8]);
#endif /* _dataFunctions_H */
