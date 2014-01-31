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
	if(argc > 1 && strcmp(argv[1], "--help") == 0) {
		std::cout << "Conway's game of life ncurses implementation.\n";
		std::cout << "Needs libncursesw and terminal with colour and Unicode support.\n";
		std::cout << "Usage:\n";
		std::cout << "\tlife --help\n";
		std::cout << "\tlife PATTERN_NAME\n";
		std::cout << "\tlife FILE_NAME\n";
		std::cout << "PATTERN_NAME is a name from the list below. If no such pattern exists,\n";
		std::cout << "it is treated as a file name.\n";
		std::cout << '\n';
		std::cout << "Pattern list:\n";
		PatternFactory::print_list();
		std::cout << std::endl;
		return 0;
	}
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
