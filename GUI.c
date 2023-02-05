#include <ncurses.h>

int main(int argc, char **argv)
{
	char c;
	initscr();

    	// creating a window;
    	// with height = 15 and width = 10
   	// also with start x axis 10 and start y axis = 20
    	WINDOW *win = newwin(30, 30, 0, 0);
    	refresh();

    	// making box border with default border styles
    	//box(win, 0, 0);

    	// move and print in window
    	mvwprintw(win, 0, 1, "Greeter");
    	mvwprintw(win, 1, 1, "Hello");

    	// refreshing the window
    	wrefresh(win);

    	//c = getch();
	//mvprintw(win, 0, 5, c);
	//wrefresh(win);
	getch();
    	endwin();
    	return 0;
}
