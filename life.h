/** life.h - Conway's Game of Life definition and management.
 * author antifin
 * version 1.0.1
 * license WTFPLv2
 */

#pragma once

const int HASH_COUNT = 10;

struct Life {
	int *map,*buffer;
	int width,height;
	unsigned int hashes[HASH_COUNT];
	int currentHashIndex;
};

Life* newLife(int width,int height);
void bigBang(Life *life);
void tick(Life *life);
void freeLife(Life *life);
unsigned hash(int *a, unsigned c);


