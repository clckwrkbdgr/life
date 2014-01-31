#include "seeds.h"
#include "life.h"
#include "patterns.h"
#include "console.h"
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cstring>

int main(int argc, char ** argv)
{
	srand(time(NULL));
	Ncurses display;
	PatternFactory patterns;
	LifeSeed * seed = 0;
	if(argc > 1) {
		if(patterns.has_pattern(argv[1])) {
			seed = new TextSeed(patterns.get_pattern(argv[1]));
		} else {
			std::ifstream file(argv[1]);
			seed = new StreamSeed(file, display.width(), display.height());
		}
	}
	Life life(display.width(), display.height(), seed);
	while(!display.quit()) {
		display.output(life);
		life.tick();
	}
	return 0;
}
