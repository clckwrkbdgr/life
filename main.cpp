#include "life.h"
#include "console.h"
#include <ctime>
#include <cstdlib>

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

void seed_from_text(const char * text, Cell * map, int width, int height)
{
	std::fill(map, map + width * height, 0);
	int pos = 0;
	for(const char * ch = text; *ch != 0; ++ch) {
		if(*ch == '\n') {
			pos = 0;
			map += width;
		} else {
			map[pos++] = (*ch == ' ' ? 0 : 1);
		}
	}
}

void glider_seed(Cell * map, int width, int height)
{
	seed_from_text(glider, map, width, height);
}

void gun_seed(Cell * map, int width, int height)
{
	seed_from_text(gun, map, width, height);
}


int main(int /*argc*/, char ** /*argv*/)
{
	srand(time(NULL));
	Ncurses display;
	Life life(display.width(), display.height(), gun_seed);
	while(!display.quit()) {
		display.output(life);
		life.tick();
	}
	return 0;
}
