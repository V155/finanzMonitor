#include <ncurses.h>

void drawLine(int length);
void drawTableSeparatorLine(char specialCharacter);
void drawSpecialCharacter(char specialCharacter);
void nAddEntry();
WINDOW *create_newwin(int height, int width ,int starty, int startx);
void destroy_win(WINDOW *local_win);
int input(void);
void smallOutput(void);
int output(void);
void ncursesOutput(void);
