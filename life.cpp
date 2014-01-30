#include <cstdlib>
#include "life.h"
const int HASH_COUNT = 10;

struct BigBang : LifeSeed {
	void run(Cell * map, int width, int height)
	{
		for(int i = 0; i < width * height; i++) {
			map[i] = (rand() % 2);
		}
	}
};

Life::Life(int field_width, int field_height, LifeSeed * life_seed)
	: width(field_width), height(field_height),
	map(width * height, 0), buffer(width * height, 0),
	hashes(HASH_COUNT, 0), current_hash_index(0),
	seed(life_seed ? life_seed : new BigBang())
{
	restart();
}

void Life::tick()
{
	unsigned h = 0, g = 0;
	for(int x = 0; x < width; x++) {
		for(int y = 0; y < height; y++) {
			int index = x + y * width;

			int top    = (y <= 0)          ? (height - 1) : (y - 1);
			int bottom = (y >= height - 1) ? 0            : (y + 1);
			int left   = (x <= 0)          ? (width - 1)  : (x - 1);
			int right  = (x >= width - 1)  ? 0            : (x + 1);
			int neighbours = 
				map[left  + width * top   ] +
				map[x     + width * top   ] +
				map[right + width * top   ] +
				map[right + width * y     ] +
				map[right + width * bottom] +
				map[x     + width * bottom] +
				map[left  + width * bottom] +
				map[left  + width * y     ];

			// B3/S23
			if(neighbours == 3) {
				buffer[index] = 1;
			} else if(neighbours == 2) {
				buffer[index] = map[index];
			} else {
				buffer[index] = 0;
			}

			// Hash.
			h = (h << 4) + buffer[index];
			if((g = (h & 0xf0000000))) {
				h ^= g >> 23;
			}
			h &= ~g;
		}
	}

	// Swap planes.
	map.swap(buffer);

	// Loop detection.
	unsigned int currentHash = h;
	for(int i = 0; i < HASH_COUNT; i++) {
		bool loopIsDetected = hashes[i] == currentHash;
		if(loopIsDetected) {
			restart();
			break;
		}
	}

	hashes[current_hash_index] = currentHash;
	current_hash_index++;
	while(current_hash_index >= HASH_COUNT) {
		current_hash_index -= HASH_COUNT;
	}
}

void Life::restart()
{
	seed->run(&map.front(), width, height);
}

