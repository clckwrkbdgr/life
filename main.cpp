#include <ncurses.h>
#include <cstdlib>

#include "life.h"

int main()
{
	// ncurses init.
	initscr();
	noecho();
	cbreak();
	halfdelay(1);

	// Create life structures.
	int width,height;
	getmaxyx(stdscr,height,width);
	Life life(width,height,2,1);
	life.bigBang();

	// Main cycle.
	while(getch() != 'q')
	{
		// Draw.
		erase();

		for(int x=0;x<life.width();x++)
			for(int y=0;y<life.height();y++)
				if(life.cell(x,y))
					mvaddch(y,x,'@');

		refresh();

		if(!life.tick())
			life.bigBang();
	}

	// End ncurses mode and quit.
	echo();
	endwin();
	return 0;
}

