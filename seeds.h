#pragma once
#include "life.h"
#include <iostream>

struct TextSeed : LifeSeed {
	const char * text;
	TextSeed(const char * seed_text) : text(seed_text) {}
	virtual void run(Cell * map, int width, int height);
};

struct StreamSeed : LifeSeed {
	StreamSeed(std::istream & stream, int width, int height);
	bool has_content() const;
	void run(Cell * map, int /*width*/, int /*height*/);
private:
	std::vector<Cell> pattern;
};

