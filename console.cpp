#include "console.h"
#include "life.h"
#include <ncursesw/ncurses.h>
#include <locale.h>

Ncurses::Ncurses()
	: Display()
{
	setlocale(LC_ALL, "");
	initscr();
	noecho();
	cbreak();
	curs_set(FALSE);
	halfdelay(1);
	int rows, cols;
	getmaxyx(stdscr, rows, cols);
	setWidth(cols);
	setHeight(rows * 2);

	start_color();
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	init_pair(2, COLOR_BLACK, COLOR_BLUE);
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

	for(int x = 0; x < life.width; x++) {
		for(int y = 0; y < life.height; y += 2) {
			bool up = life.map[x + (y) * life.width] == 1;
			bool down = life.map[x + (y + 1) * life.width] == 1;

			cchar_t t;
			t.attr = COLOR_PAIR(1);
			t.chars[1] = 0;

			move(y / 2, x);
			if(up && down) {
				t.attr = COLOR_PAIR(2);
				t.chars[0] = ' ';
			} else if(up) {
				t.attr = COLOR_PAIR(2);
				t.chars[0] = 0x2584;
			} else if(down) {
				t.attr = COLOR_PAIR(1);
				t.chars[0] = 0x2584;
			} else {
				t.attr = COLOR_PAIR(1);
				t.chars[0] = ' ';
			}
			add_wch(&t);
		}
	}

	refresh();
}

