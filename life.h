#pragma once
#include <vector>

typedef char Cell;
typedef void (*LifeSeed)(Cell * array, int width, int height);

struct Life {
	typedef std::vector<Cell> Map;
	int width, height;
	Map map, buffer;
	std::vector<unsigned> hashes;
	int current_hash_index;
	LifeSeed seed;

	Life(int field_width, int field_height, LifeSeed life_seed = 0);
	void restart();
	void tick();
};

