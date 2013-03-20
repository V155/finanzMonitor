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

int main(void) {



    //strcpy(eintraege[0].kategorie, "Kat0001");
    //strcpy(eintraege[0].posten, "Posten1");
    //eintraege[0].preis = 599;
    //eintraege[0].datum = 11032013;

    //eingabe();
    //ausgabe();
    readIn();
    smallOutput();

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

    return EXIT_SUCCESS;

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

    return EXIT_SUCCESS;

}

int readIn(void) {

    FILE *savefile;	//pointer to the savefile
    char puffer[ROWLENGTH]; //char array that contains the read data
    char name[] = {"save.csv"}; //the name of the savefile

    savefile = fopen ("save.csv", "r"); //savefile is opened read-only
    if (savefile == NULL) perror ("Error opening file"); //checks if file can be opened
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

    return EXIT_SUCCESS;
}
