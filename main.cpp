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


struct TextSeed : LifeSeed {
	const char * text;
	TextSeed(const char * seed_text) : text(seed_text) {}
	void run(Cell * map, int width, int height)
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
};

int main(int /*argc*/, char ** /*argv*/)
{
	srand(time(NULL));
	Ncurses display;
	Life life(display.width(), display.height(), new TextSeed(gun));
	while(!display.quit()) {
		display.output(life);
		life.tick();
	}
	return 0;
}
