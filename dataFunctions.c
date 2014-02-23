#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include "dataFunctions.h"
#define ROWLENGTH 46



void createEntry(int* entI, struct entry* entries, char category[8], char desc[16], int price, int date)
{
	strcpy(entries[*entI].category, category);
	strcpy(entries[*entI].desc, desc);
	entries[*entI].price = price;
	entries[*entI].date = date;
	*entI += 1;
	writeOut(*entI, entries);
}
/**
//reads the data from the save.csv
int readIn(int* incI, struct fixcost* incomes, int* bilI, struct fixcost* bills, int* entI, struct entry* entries)
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
				strcpy(incomes[*incI].desc, ptr);
			ptr = strtok(NULL, ",");
			if(ptr != NULL)
				incomes[*incI].price = atoi(ptr);
			
			*incI += 1;
			
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
				strcpy(bills[*bilI].desc, ptr);
			ptr = strtok(NULL, ",");
			if(ptr != NULL)
				bills[*bilI].price = atoi(ptr);
			
			*bilI += 1;
			
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
					strcpy(entries[*entI].category , ptr);//write the content of the read field into the struct
				ptr = strtok(NULL, ",");
				if (ptr != NULL)
					strcpy(entries[*entI].desc, ptr);
				ptr = strtok(NULL, ",");
				if (ptr != NULL)
					entries[*entI].price = atoi(ptr);
				ptr = strtok(NULL, ",");
				if (ptr != NULL)
					entries[*entI].date = atoi(ptr);
				
				*entI += 1;
			}
		}
	}
	
	fclose (savefile);
	
	return 0;
}
*/
//reads the data from the save.csv
int readIn(struct month month)
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
				strcpy(month.incomes[month.incomesIndex].desc, ptr);
			ptr = strtok(NULL, ",");
			if(ptr != NULL)
				month.incomes[month.incomesIndex].price = atoi(ptr);
			
			month.incomesIndex += 1;
			
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
				strcpy(month.bills[month.billsIndex].desc, ptr);
			ptr = strtok(NULL, ",");
			if(ptr != NULL)
				month.bills[month.billsIndex].price = atoi(ptr);
			
			month.billsIndex += 1;
			
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
					strcpy(month.entries[month.entriesIndex].category , ptr);//write the content of the read field into the struct
				ptr = strtok(NULL, ",");
				if (ptr != NULL)
					strcpy(month.entries[month.entriesIndex].desc, ptr);
				ptr = strtok(NULL, ",");
				if (ptr != NULL)
					month.entries[month.entriesIndex].price = atoi(ptr);
				ptr = strtok(NULL, ",");
				if (ptr != NULL)
					month.entries[month.entriesIndex].date = atoi(ptr);
				
				month.entriesIndex += 1;
			}
		}
	}
	
	fclose (savefile);
	
	return 0;
}

int writeOut(int entriesIndex, struct entry* entries)
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
int calcSums(int entriesIndex, struct entry* entries, int numCat, int* sums, char (*knCats)[8])
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
		eq = checkKnown(entries[i].category, numCat, knCats);
		
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

int checkKnown(char cat[8], int numCat, char (*knCats)[8]){
	
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
