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

struct month
{
	int month;
	int saldoLastMonth;
	struct entry entries[100];
	struct fixcost incomes[50];
	struct fixcost bills[50];
	int entriesIndex;
	int incomesIndex;
	int billsIndex;
	int sum1;
	int sums[16];
	char knCats[16][8];
	int numCat;
};


void createEntry(int* entI, struct entry* entries, char category[8], char desc[16], int price, int date);
//int readIn(int* incI, struct fixcost* incomes, int* bilI, struct fixcost* bills, int* entI, struct entry* entries);
int readIn(struct month month);
int writeOut(int entriesIndex, struct entry* entries);
int calcSums(int entriesIndex, struct entry* entries, int numCat, int* sums, char (*knCats)[8]);
int checkKnown(char cat[8], int numCat, char (*knCats)[8]);
#endif /* _dataFunctions_H */
