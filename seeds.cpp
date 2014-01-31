#include "seeds.h"

TextSeed::TextSeed(const char * seed_text)
	: text(seed_text), pattern_width(0), pattern_height(0)
{
	int current_width = 0;
	for(const char * ch = text; *ch != 0; ++ch) {
		if(*ch == '\n') {
			++pattern_height;
			pattern_width = std::max(pattern_width, current_width);
			current_width = 0;
		} else {
			++current_width;
		}
	}
}

void TextSeed::run(Cell * map, int width, int height)
{
	Cell * end = map + width * height;
	std::fill(map, end, 0);
	int start_pos = 0;
	if(pattern_width < width && pattern_height < height) {
		map += width * ((height - pattern_height) / 2);
		start_pos = (width - pattern_width) / 2;
	}
	int pos = start_pos;
	for(const char * ch = text; *ch != 0; ++ch) {
		if(pos >= width || *ch == '\n') {
			pos = start_pos;
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
