#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#define HASH_COUNT 10

unsigned int hash(int *array, int count)
{
	unsigned int h = 0;
	unsigned int g = 0;

	for(int i = 0; i < count; i++)
	{
		h = (h << 4) + array[i];

		if((g = (h & 0xf0000000)) != 0)
			h ^= g >> 23;
		h &= ~g;
	}

	return h;
}

int main()
{
	srand(time(NULL));

	// ncurses init.
	initscr();
	noecho();
	cbreak();
	halfdelay(1);

	// Create life structures.
	int width, height;
	getmaxyx(stdscr, height, width);

	int *map = new int[width * height];
	int *buffer = new int[width * height];
	for(int i = 0; i < width * height; i++)
		map[i] = (rand() % 2);

	unsigned int *hashes = new unsigned int[HASH_COUNT];
	for(int i = 0; i < HASH_COUNT; i++)
		hashes[i] = 0;
	int currentHashIndex = 0;

	// Main cycle.
	while(getch() != 'q')
	{
		// Draw.
		erase();

		for(int x = 0; x < width; x++)
			for(int y = 0; y < height; y++)
				if(map[x + y * width])
					mvaddch(y, x, '@');

		refresh();

		// Tick.
		for(int x = 0; x < width; x++)
			for(int y = 0; y < height; y++)
			{
				int index = x + y * width;

				int top    = ((y <= 0)          ? (height - 1) : (y - 1)),
				    bottom = ((y >= height - 1) ? 0            : (y + 1)),
				    left   = ((x <= 0)          ? (width - 1)  : (x - 1)),
				    right  = ((x >= width - 1)  ? 0            : (x + 1));
				int neighbours = 
					map[left  + width * top   ] +
					map[x     + width * top   ] +
					map[right + width * top   ] +
					map[right + width * y     ] +
					map[right + width * bottom] +
					map[x     + width * bottom] +
					map[left  + width * bottom] +
					map[left  + width * y     ];

				if(neighbours < 2 || neighbours > 3)
					buffer[index] = 0; // Die.
				else if(neighbours == 3 && map[index] == 0)
					buffer[index] = 1; // Live.
				else
					buffer[index] = map[index];
			}

		// Hashing.		
		unsigned int currentHash = hash(map, width * height);
		for(int i = 0; i < HASH_COUNT; i++)
			if(hashes[i] == currentHash) // Cycling detected.
			{
				// Big bang.
				for(int i = 0; i < width * height; i++)
					buffer[i] = (rand() % 2);
			}
		hashes[currentHashIndex] = currentHash;
		currentHashIndex++;
		while(currentHashIndex >= HASH_COUNT)
			currentHashIndex -= HASH_COUNT;

		// Swap planes.
		int *tmp = map;
		map = buffer;
		buffer = tmp;
	}

	// End ncurses mode and quit.
	delete []map;
	delete []buffer;
	delete []hashes;

	echo();
	endwin();
	return 0;
}

