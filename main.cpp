#include "life.h"
#include "console.h"
#include "graphic.h"
#include "life.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

int resolution_arg_to_string(const char * str)
{
	int result = atoi(str);
	if(result == 0) {
		std::cerr << "'" << str << "' is wrong resolution parameter!\n";
		exit(1);
	}
	return result;
}

int main(int argc, char ** argv)
{
	if(argc > 2) {
		SDLDisplay::WIDTH  = resolution_arg_to_string(argv[1]);
		SDLDisplay::HEIGHT = resolution_arg_to_string(argv[2]);
	}
	Ncurses display;

	srand(time(NULL));

	Life *life = newLife(display.width(), display.height());
	bigBang(life);
	while(!display.quit()) {
		display.prepareOutput();
		for(int x = 0; x < life->width; x++) {
			for(int y = 0; y < life->height; y++) {
				display.output(x, y, life->map[x + y * life->width]);
			}
		}
		display.doneOutput();

		tick(life);
	}
	freeLife(life);

	return 0;
}
