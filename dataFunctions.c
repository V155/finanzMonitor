#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include "dataFunctions.h"
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
//int containing the sum of the entries with category==KAT1
int sum1 = 0;
//stores the sums of the categories
int sums[16];
//stores the names of the categories
char knCats[16][8];
//stores the number of found categories
int numCat = 0;


void createEntry(char category[8], char desc[16], int price, int date)
{
	strcpy(entries[entriesIndex].category, category);
	strcpy(entries[entriesIndex].desc, desc);
	entries[entriesIndex].price = price;
	entries[entriesIndex].date = date;
	entriesIndex++;
	writeOut();
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
