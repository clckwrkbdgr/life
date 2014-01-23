#include "console.h"
#include <ncurses.h>

Ncurses::Ncurses()
	: Display()
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
	if(value) {
		mvaddch(y, x, '0');
	}
}

void Ncurses::doneOutput() {
	refresh();
}
