/** life.cpp - Conway's Game of Life definitioin and management.
 * author antifin
 * version 2.0.0
 * license WTFPLv2
 */

#include <cstdlib>
#include "life.h"

void tick(Life *life)
{
	for(int x = 0; x < life->width; x++)
		for(int y = 0; y < life->height; y++) {
			int index = x + y * life->width;

			int top    = ((y <= 0)                ? (life->height - 1) : (y - 1)),
			    bottom = ((y >= life->height - 1) ? 0                  : (y + 1)),
			    left   = ((x <= 0)                ? (life->width - 1)  : (x - 1)),
			    right  = ((x >= life->width - 1)  ? 0                  : (x + 1));
			int neighbours = 
				life->map[left  + life->width * top   ] +
				life->map[x     + life->width * top   ] +
				life->map[right + life->width * top   ] +
				life->map[right + life->width * y     ] +
				life->map[right + life->width * bottom] +
				life->map[x     + life->width * bottom] +
				life->map[left  + life->width * bottom] +
				life->map[left  + life->width * y     ];

			// B3/S23
			if(neighbours < 2 || neighbours > 3)
				life->buffer[index] = 0; // Die.
			else if(neighbours == 3 && life->map[index] == 0)
				life->buffer[index] = 1; // Live.
			else
				life->buffer[index] = life->map[index];
		}

	// Swap planes.
	int *tmp = life->map;
	life->map = life->buffer;
	life->buffer = tmp;

	// Loop detection.
	unsigned int currentHash = hash(life->map, life->width * life->height);
	for(int i = 0; i < HASH_COUNT; i++) {
		bool loopIsDetected = life->hashes[i] == currentHash;
		if(loopIsDetected)
			bigBang(life);
	}

	life->hashes[life->currentHashIndex] = currentHash;
	life->currentHashIndex++;
	while(life->currentHashIndex >= HASH_COUNT)
		life->currentHashIndex -= HASH_COUNT;
}

void bigBang(Life *life)
{
	for(int i = 0; i < life->width * life->height; i++)
		life->map[i] = (rand() % 2);
}

Life* newLife(int width,int height)
{
	Life *life = new Life;
	life->width = width;
	life->height = height;

	life->map = new int[life->width * life->height];
	life->buffer = new int[life->width * life->height];

	for(int i = 0; i < HASH_COUNT; i++)
		life->hashes[i] = 0;
	life->currentHashIndex = 0;

	return life;
}

void freeLife(Life *life)
{
	delete []life->map;
	delete []life->buffer;
	delete life;
}

unsigned hash(int *a, unsigned c)
{
	unsigned h=0,g=0;
	for(unsigned i=0;i<c;++i) {
		h=(h<<4)+a[i];
		if((g=(h&0xf0000000))) h^=g>>23;
		h&=~g;
	}
	return h;
}
