#include <ncurses.h>

int main(void){
	char c;
	initscr();

	refresh();

	while(1){
		refresh();
		c = getch() ;
		move(0,0);
		printw("You entered: ");
	}
	endwin();
	return 0;
}
