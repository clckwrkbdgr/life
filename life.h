#pragma once
#include <vector>

struct Life {
	typedef std::vector<char> Map;
	int width, height;
	Map map, buffer;
	std::vector<unsigned> hashes;
	int current_hash_index;

	Life(int field_width, int field_height);
	void bigBang();
	void tick();
};

