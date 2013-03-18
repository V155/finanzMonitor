#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ZEILENLAENGE 46

struct eintrag{
    char kategorie[8];
    char posten[16];
    int preis;
    int datum;
};

struct eintrag eintraege[100];
int aktIndex = 0;
char buf[16];

int main(void) {



    //strcpy(eintraege[0].kategorie, "Kat0001");
    //strcpy(eintraege[0].posten, "Posten1");
    //eintraege[0].preis = 599;
    //eintraege[0].datum = 11032013;

    //eingabe();
    //ausgabe();
    readIn();
    ausgabe();

    return EXIT_SUCCESS;
}
int eingabe(void){

    char kategorie[8];
    char posten[16];
    int preis;
    int datum;

    printf("Bitte Kategorie eingeben : ");
    fgets(buf, 7, stdin);
    sscanf(buf, "%s", &kategorie);
    memset(buf,'+',16);
    printf("Bitte Posten eingeben : ");
    fgets(buf, 15, stdin);
    sscanf(buf, "%s", &posten);
    memset(buf, '\0',16);
    printf("Bitte Preis eingeben : ");
    fgets(buf, 8, stdin);
    sscanf(buf, "%d", &preis);
    memset(buf, '\0',strlen(buf));
    printf("Bitte Datum eingeben : ");
    fgets(buf, 9, stdin);
    sscanf(buf, "%d", &datum);
    memset(buf, '\0',strlen(buf));

    strcpy(eintraege[aktIndex].kategorie , kategorie);
    strcpy(eintraege[aktIndex].posten, posten);
    eintraege[aktIndex].preis = preis;
    eintraege[aktIndex].datum = datum;

    return EXIT_SUCCESS;

}

int ausgabe(void) {

    int i = 0;

    for(i=0; i < aktIndex; i++){

	printf ("*------------------------------------------*\n");
	printf ("* PostenNr:...........................%4d *\n", i);
	printf ("* Kategorie:......................%8s *\n", eintraege[i].kategorie);
	printf ("* PostenB:................%16s *\n", eintraege[i].posten);
	printf ("* Preis:..........................%8d *\n", eintraege[i].preis);
	printf ("* Datum:..........................%8d *\n", eintraege[i].datum);
	printf ("*------------------------------------------*\n");

    }

    return EXIT_SUCCESS;

}

int readIn(void) {

    FILE *savefile;
    char puffer[ZEILENLAENGE];
    char name[] = {"save.csv"};

    savefile = fopen ("save.csv", "r");
    if (savefile == NULL) perror ("Error opening file");
    else {
	int i = 1;
	char *ptr;
	while ( fgets (puffer , ZEILENLAENGE , savefile) != NULL ){
	    //puts (puffer);
	    
	    ptr = strtok(puffer, ",");
	    if (ptr != NULL)		
		strcpy(eintraege[aktIndex].kategorie , ptr);
	    ptr = strtok(NULL, ",");
	    if (ptr != NULL)
		strcpy(eintraege[aktIndex].posten, ptr);
	    ptr = strtok(NULL, ",");
	    if (ptr != NULL)
		eintraege[aktIndex].preis = atoi(ptr);
	    ptr = strtok(NULL, ",");
	    if (ptr != NULL)
		eintraege[aktIndex].datum = atoi(ptr);

	    aktIndex ++;
	}


    }

    
    fclose (savefile);


    return EXIT_SUCCESS;
}
