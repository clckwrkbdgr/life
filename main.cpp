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


struct TextSeed : LifeSeed {
	const char * text;
	TextSeed(const char * seed_text) : text(seed_text) {}
	void run(Cell * map, int width, int height)
	{
		Cell * end = map + width * height;
		std::fill(map, end, 0);
		int pos = 0;
		for(const char * ch = text; *ch != 0; ++ch) {
			if(pos >= width || *ch == '\n') {
				pos = 0;
				map += width;
				if(map == end) {
					break;
				}
			} else {
				map[pos++] = (*ch == ' ' ? 0 : 1);
			}
		}
	}
};

struct StreamSeed : LifeSeed {
	bool has_content() const
	{
		return !pattern.empty();
	}
	StreamSeed(std::istream & stream, int width, int height)
		: pattern(width * height, 0)
	{
		if(!stream.good()) {
			pattern.clear();
			return;
		}
		int pos = 0;
		char ch;
		std::vector<Cell>::iterator map = pattern.begin();
		stream.unsetf(std::ios::skipws);
		while(stream.good()) {
			stream >> ch;
			if(pos >= width || ch == '\n') {
				pos = 0;
				map += width;
				if(map == pattern.end()) {
					break;
				}
			} else {
				*(map + pos++) = (ch == ' ' ? 0 : 1);
			}
		}
	}
	void run(Cell * map, int /*width*/, int /*height*/)
	{
		if(has_content()) {
			std::copy(pattern.begin(), pattern.end(), map);
		}
	}
private:
	std::vector<Cell> pattern;
};

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
