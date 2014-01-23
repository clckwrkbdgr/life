#include "console.h"
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

void Ncurses::prepareOutput()
{
	erase();
}

void Ncurses::output(int x, int y, int value)
{
	if(double_width_char) {
		if(value) {
			mvaddch(y, x * 2, CELL);
			mvaddch(y, x * 2 + 1, CELL);
		}
	} else {
		if(value) {
			mvaddch(y, x, CELL);
		}
	}
}

void Ncurses::doneOutput() {
	refresh();
}
