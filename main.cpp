#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#define HASH_COUNT 10

struct Life {
	int *map,*buffer;
	int width,height;
};

Life* newLife(int width,int height);
void bigBang(Life *life);
void tick(Life *life);
void print(Life *life);
void freeLife(Life *life);

unsigned int hash(int *array, int count);

int main() {
	
	srand(time(NULL));

	// ncurses init.
	initscr();
	noecho();
	cbreak();
	halfdelay(1);

	// Create life structures.
	int rows, cols;
	getmaxyx(stdscr, rows, cols);
	Life *life = newLife(cols, rows);

	unsigned int *hashes = new unsigned int[HASH_COUNT];
	for(int i = 0; i < HASH_COUNT; i++)
		hashes[i] = 0;
	int currentHashIndex = 0;

	// Main cycle.
	while(getch() != 'q') {
		// Draw.
		print(life);

		// Tick.
		tick(life);

		// Hashing.		
		unsigned int currentHash = hash(life->map, life->width * life->height);
		for(int i = 0; i < HASH_COUNT; i++)
			if(hashes[i] == currentHash) // Cycling detected.
				bigBang(life);

		hashes[currentHashIndex] = currentHash;
		currentHashIndex++;
		while(currentHashIndex >= HASH_COUNT)
			currentHashIndex -= HASH_COUNT;

	}

	// End ncurses mode and quit.
	freeLife(life);
	delete []hashes;

	echo();
	endwin();
	return 0;
}


/** Hashinh function for life map.
 * @param array Array for hashing.
 * @param count Size of array.
 * @return Value of hash.
 */
unsigned int hash(int *array, int count) {
	unsigned int h = 0;
	unsigned int g = 0;

	for(int i = 0; i < count; i++) {
		h = (h << 4) + array[i];

		if((g = (h & 0xf0000000)) != 0)
			h ^= g >> 23;
		h &= ~g;
	}

	return h;
}


/** Performs one game tick.
 * Calculaters next generation basing on rule B3/S23.
 * @param life Life object.
 */
void tick(Life *life) {
	for(int x = 0; x < life->width; x++)
		for(int y = 0; y < life->height; y++) {
			int index = x + y * life->width;

			int top    = ((y <= 0)               ? (life->height - 1) : (y - 1)),
			    bottom = ((y >= life->height - 1) ? 0            : (y + 1)),
			    left   = ((x <= 0)               ? (life->width - 1)  : (x - 1)),
			    right  = ((x >= life->width - 1)  ? 0            : (x + 1));
			int neighbours = 
				life->map[left  + life->width * top   ] +
				life->map[x     + life->width * top   ] +
				life->map[right + life->width * top   ] +
				life->map[right + life->width * y     ] +
				life->map[right + life->width * bottom] +
				life->map[x     + life->width * bottom] +
				life->map[left  + life->width * bottom] +
				life->map[left  + life->width * y     ];

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
}


/** Prints current generation's image out on screen.
 * @param life Life object.
 */
void print(Life *life) {
	erase();

	for(int x = 0; x < life->width; x++)
		for(int y = 0; y < life->height; y++)
			if(life->map[x + y * life->width])
				mvaddch(y, x, '@');

	refresh();
}


/** Creates a burst of life cells all over the map.
 * @param life Life object.
 */
void bigBang(Life *life) {
	for(int i = 0; i < life->width * life->height; i++)
		life->map[i] = (rand() % 2);
}


/** Creates a new life object and returns pointer to it.
 * Also starts a random generation using bigBang().
 * @param width Width of the map.
 * @param height Height of the map.
 * @return Pointer to the created life object.
 */
Life* newLife(int width,int height) {
	Life *life = new Life;
	life->width = width;
	life->height = height;

	life->map = new int[life->width * life->height];
	life->buffer = new int[life->width * life->height];
	bigBang(life);

	return life;
}


/** Frees memory assigned to object <b>life</b>.
 * @param life Life object.
 */
void freeLife(Life *life) {
	delete []life->map;
	delete []life->buffer;
	delete life;
}


