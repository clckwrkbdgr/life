#include "seeds.h"
#include "life.h"
#include "console.h"
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cstring>

static const char glider[] =
"@ @\n"
" @@\n"
" @ \n"
;

static const char gun[] =
"                           @\n"
"                          @ @\n"
"         @@               @@ @\n"
"         @ @              @@ @@   @@\n"
"    @@      @             @@ @    @@\n"
"@@ @  @  @  @             @ @\n"
"@@  @@      @              @\n"
"         @ @              \n"
"         @@               \n"
;

int main(int argc, char ** argv)
{
	srand(time(NULL));
	Ncurses display;
	StreamSeed * file_seed = 0;
	if(argc > 1) {
		std::ifstream file(argv[1]);
		file_seed = new StreamSeed(file, display.width(), display.height());
	}
	LifeSeed * seed = 0;
	if(file_seed && file_seed->has_content()) {
		seed = file_seed;
	}
	Life life(display.width(), display.height(), seed);
	while(!display.quit()) {
		display.output(life);
		life.tick();
	}
	return 0;
}
