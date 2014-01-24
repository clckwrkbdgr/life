#include "console.h"
#include "life.h"
#include <ncurses.h>

static chtype CELL = '0';

Ncurses::Ncurses()
	: Display(), double_width_char(false)
{
	initscr();
	noecho();
	cbreak();
	curs_set(FALSE);
	halfdelay(1);
	int rows, cols;
	getmaxyx(stdscr, rows, cols);
	setWidth(cols);
	setHeight(rows);

	if(has_colors()) {
		start_color();
		init_pair(1, COLOR_BLACK, COLOR_BLUE);
		CELL = ' ' | COLOR_PAIR(1);
		setWidth(width() / 2);
		double_width_char = true;
	}
}

Ncurses::~Ncurses()
{
	echo();
	endwin();
}

bool Ncurses::quit() const
{
	return getch() == 'q';
}

void Ncurses::output(const Life & life)
{
	erase();

	if(double_width_char) {
		for(int x = 0; x < life.width; x++) {
			for(int y = 0; y < life.height; y++) {
				if(life.map[x + y * life.width]) {
					mvaddch(y, x * 2, CELL);
					mvaddch(y, x * 2 + 1, CELL);
				}
			}
		}
	} else {
		for(int x = 0; x < life.width; x++) {
			for(int y = 0; y < life.height; y++) {
				if(life.map[x + y * life.width]) {
					mvaddch(y, x, CELL);
				}
			}
		}
	}

	refresh();
}

