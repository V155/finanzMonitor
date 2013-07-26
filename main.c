#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ROWLENGTH 46

struct entry{ //the struct that represents one entry
    char category[8]; //a char to store the category
    char desc[16]; //a char to store the description
    int price; //an int to store the price in cents
    int date; //an int to store the date without the dots in format ddMMYYYY
};

struct entry entries[100]; //an array with length 100 to store the entries forat least a month
int actIndex = 0; //the actual index while accessing the entries array
char buf[16]; //an char array that stores the userinput
int sum1 = 0; //int containing the sum of the entries with category==KAT1
int sums[16];		//stores the sums of the categories
char knCats[16][8];	//stores the names of the categories
int numCat = 0;		//stores the number of found categories

int main(void) {

    readIn();
    smallOutput();


    /*
	strcpy(entries[actIndex].category, "KAT1");
    strcpy(entries[actIndex].desc, "Posten1");
    entries[actIndex].price = 599;
    entries[actIndex].date = 11032013;
	actIndex++;
	*/
    //eingabe();
    //ausgabe();
	calcSums();
	writeOut();

    return EXIT_SUCCESS;
}
int input(void){

    char category[8];
    char desc[16];
    int price;
    int date;

    printf("Please enter Category : ");// just the whole input sequence here
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
//    memset(buf, '\0',strlen(buf));
    printf("Please enter date : ");
    fgets(buf, 9, stdin);
    sscanf(buf, "%d", &date);
//    memset(buf, '\0',strlen(buf));

    strcpy(entries[actIndex].category , category);//copy the read values into the array of structs
    strcpy(entries[actIndex].desc, desc);
    entries[actIndex].price = price;
    entries[actIndex].date = date;

	actIndex++;

    return 0;

}

int smallOutput(void) {

	int i = 0; //just an int to iterate over the array of structs

	printf("*------+----------+------------------+----------+----------*\n");
	printf("* Nr   | Category | Description      | Price    | Date     *\n");
	printf("*------+----------+------------------+----------+----------*\n");

	for(i=0; i< actIndex; i++){
		printf("* %4d | %8s | %16s | %8d | %8d *\n", i, entries[i].category, entries[i].desc, entries[i].price, entries[i].date);
	}

	printf("*------+----------+------------------+----------+----------*\n");
}

int output(void) {

    int i = 0; //just an int to iterate over the array of structs

    for(i=0; i < actIndex; i++){ //an iteration over all the entries and output of them

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

int readIn(void) {

    FILE *savefile;	//pointer to the savefile
    char puffer[ROWLENGTH]; //char array that contains the read data
    char name[] = {"save.csv"}; //the name of the savefile

    savefile = fopen ("save.csv", "r"); //savefile is opened read-only
    if (savefile == NULL){
	   	perror ("Error opening file"); //checks if file can be opened
		return 1;
	}
    else {
		char *ptr; //pointer to store the fields of the csv in
		while ( fgets (puffer , ROWLENGTH , savefile) != NULL ){ //read all lines of file

			//expected file format: category,shortdescription,priceInCent,date
			ptr = strtok(puffer, ","); //read in the first field
			if (ptr != NULL)// check if there was a field
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

int writeOut(void){
	
	int i=0;
	FILE *savefile;	//pointer to the savefile
    char puffer[ROWLENGTH]; //char array that contains the read data
    char name[] = {"save.csv"}; //the name of the savefile

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

int calcSums(void){ //calculates the Sum of expenses for each category

		
	int eq = 0;			//needed for the known category check
	int i = 0;
	for(i=0; i < actIndex; i++){
//	printf("Starting sum calculation %d\n",i);
//	printf("kat: %s\n", entries[i].category); 
//		if(0==strcmp(entries[i].category, "KAT1")){ //equals KAT1
			
//			k = k + entries[i].price;
//			printf("SUM1: %d\n",k);
		//}
	
//	}
//	k=strcmp("KAT1","KAT1");
//	printf("Equal:  %d\n", k);
//	printf("SUM: %d\n", k);
	
		eq = checkKnown(entries[i].category);		//returns index of category in knCats array if known. else -1

		if(eq == -1){
			strcpy(knCats[numCat], entries[i].category);		//append the category to the known categories array
			sums[numCat] = entries[i].price;
			numCat++;
		}
		else{
			sums[eq] = sums[eq] + entries[i].price;		//increase the sum by the price of the actual entry
		}
	}//for loop

	int mainSum = 0;
	
	for (i = 0 ; i < numCat; i++){
		printf("Sum of %s is : %d\n", knCats[i], sums[i]);
		mainSum += sums[i];
	}
	printf("Overall Sum: %d\n", mainSum);

	return 1;
}

int checkKnown(char cat[8]){
	
	int e = 0;	//stores 0 if equal and 1 if not
	int k = 0;	//var for the second loop
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

