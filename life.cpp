#include <cstdlib>
#include "life.h"
const int HASH_COUNT = 10;

template<class Iterator>
unsigned hash(Iterator start, Iterator stop)
{
	unsigned h = 0, g = 0;
	for(Iterator current = start; current != stop; ++current) {
		h = (h << 4) + *current;
		if(g = (h & 0xf0000000)) {
			h ^= g >> 23;
		}
		h &= ~g;
	}
	return h;
}


Life::Life(int field_width, int field_height)
	: width(field_width), height(field_height),
	map(width * height, 0), buffer(width * height, 0),
	hashes(HASH_COUNT, 0), current_hash_index(0)
{
}

void Life::tick()
{
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
			if(neighbours < 2 || neighbours > 3) {
				buffer[index] = 0; // Die.
			} else if(neighbours == 3 && map[index] == 0) {
				buffer[index] = 1; // Live.
			} else {
				buffer[index] = map[index];
			}
		}
	}

	// Swap planes.
	map.swap(buffer);

	// Loop detection.
	unsigned int currentHash = hash(map.begin(), map.end());
	for(int i = 0; i < HASH_COUNT; i++) {
		bool loopIsDetected = hashes[i] == currentHash;
		if(loopIsDetected) {
			bigBang();
			break;
		}
	}

	hashes[current_hash_index] = currentHash;
	current_hash_index++;
	while(current_hash_index >= HASH_COUNT) {
		current_hash_index -= HASH_COUNT;
	}
}

void Life::bigBang()
{
	for(int i = 0; i < width * height; i++) {
		map[i] = (rand() % 2);
	}
}

