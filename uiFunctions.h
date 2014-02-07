#include <ncurses.h>
#include "dataFunctions.h"

void drawLine(int length);
void drawTableSeparatorLine(char specialCharacter);
void drawSpecialCharacter(char specialCharacter);
void nAddEntry();
WINDOW *create_newwin(int height, int width ,int starty, int startx);
void destroy_win(WINDOW *local_win);
int input(int, struct entry*);
void smallOutput(int incomesIndex, struct fixcost* incomes, int billsIndex, struct fixcost* bills, int entriesIndex, struct entry* entries, int numCat, char (*knCats)[8], int* sums, int sum1);
int output(int entriesIndex, struct entry* entries);
void ncursesOutput(int incomesIndex, struct fixcost* incomes, int billsIndex, struct fixcost* bills, int entriesIndex, struct entry* entries, int sum1, int numCat, char (*knCats)[8], int* sums);
