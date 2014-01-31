#include "seeds.h"

void TextSeed::run(Cell * map, int width, int height)
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


StreamSeed::StreamSeed(std::istream & stream, int width, int height)
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

bool StreamSeed::has_content() const
{
	return !pattern.empty();
}

void StreamSeed::run(Cell * map, int /*width*/, int /*height*/)
{
	if(has_content()) {
		std::copy(pattern.begin(), pattern.end(), map);
	}
}
