#include "life.h"
#include "console.h"
#include "graphic.h"
#include "life.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>

int resolution_arg_to_string(const char * str)
{
	int result = atoi(str);
	if(result == 0) {
		std::cerr << "'" << str << "' is wrong resolution parameter!\n";
		exit(1);
	}
	return result;
}

void run(Display & display)
{
	Life life(display.width(), display.height());
	life.bigBang();
	while(!display.quit()) {
		display.prepareOutput();
		for(int x = 0; x < life.width; x++) {
			for(int y = 0; y < life.height; y++) {
				display.output(x, y, life.map[x + y * life.width]);
			}
		}
		display.doneOutput();

		life.tick();
	}
}

int main(int argc, char ** argv)
{
	if(argc > 2) {
		SDLDisplay::WIDTH  = resolution_arg_to_string(argv[1]);
		SDLDisplay::HEIGHT = resolution_arg_to_string(argv[2]);
	}
	enum Mode { CURSES, SDL };
	Mode mode = CURSES;
	if(argc > 1) {
		if(strcmp(argv[1], "curses") == 0) {
			mode = CURSES;
		} else if(strcmp(argv[1], "sdl") == 0) {
			mode = SDL;
		} else {
			std::cerr << "<" << argv[1] << "> is wrong display mode.\n";
			std::cerr << "Possible values:\n";
			std::cerr << "\tcurses - for ncurses console version.\n";
			std::cerr << "\tsdl    - for graphical version using SDL.\n";
			return 1;
		}
	}
	
	srand(time(NULL));

	switch(mode) {
		case CURSES:
			{
				Ncurses display;
				run(display);
				break;
			}
		case SDL:
			{
				SDLDisplay display;
				run(display);
				break;
			}
	}
	return 0;
}
