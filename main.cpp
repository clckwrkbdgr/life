/** main.cpp - Conway's Game of Life.
 * author antifin
 * version 1.0.1
 * license WTFPLv2
 */

#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <SDL/SDL.h>
#include "life.h"

class Display {
public:
	Display() : w(0), h(0) {}
	virtual ~Display() {}

	int width() const { return w; }
	int height() const { return h; }
	void setWidth(int value) { w = value; }
	void setHeight(int value) { h = value; }

	virtual bool quit() const = 0;
	virtual void prepareOutput() = 0;
	virtual void output(int x, int y, int value) = 0;
	virtual void doneOutput() = 0;
private:
	int w, h;
};

class Ncurses : public Display {
public:
	Ncurses() : Display() {
		initscr();
		noecho();
		cbreak();
		halfdelay(1);
		int rows, cols;
		getmaxyx(stdscr, rows, cols);
		setWidth(cols);
		setHeight(rows);
	}
	virtual ~Ncurses() {
		echo();
		endwin();
	}
	virtual bool quit() const {
		return getch() == 'q';
	}

	virtual void prepareOutput() {
		erase();
	}
	virtual void output(int x, int y, int value) {
		if(value) {
			mvaddch(y, x, '@');
		}
	}
	virtual void doneOutput() {
		refresh();
	}
};

class SDLDisplay : public Display {
public:
	enum { VIDEODEPTH = 32 };
	SDL_Surface * screen;

	SDLDisplay() : Display(), screen(NULL) {
		if(SDL_Init(SDL_INIT_VIDEO) < 0) {
			fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
			exit(1);
		}
		atexit(SDL_Quit);

		setWidth(640);
		setHeight(480);
		screen = SDL_SetVideoMode(width(), height(), VIDEODEPTH, SDL_SWSURFACE);
		if(!screen) {
			fprintf(stderr, "Unable to set %dx%dx%d video mode: %s\n", width(), height(), VIDEODEPTH, SDL_GetError());
			exit(1);
		}
	}
	virtual ~SDLDisplay() {
		if(screen) {
			SDL_FreeSurface(screen);
		}
	}
	virtual bool quit() const {
		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type) {
			case SDL_KEYDOWN: return true;
			case SDL_QUIT: return true;
		}
		return false;
	}

	virtual void prepareOutput() {
		SDL_FillRect(screen,NULL,0x000000);
		if( SDL_MUSTLOCK( screen ) ) {
			SDL_LockSurface( screen );
		} 
	}
	virtual void output(int x, int y, int value) {
		if(value) {
			put_pixel32(screen, x, y, 0xffffff);
		}
	}
	virtual void doneOutput() {
		if( SDL_MUSTLOCK( screen ) ) {
			SDL_UnlockSurface( screen );
		} 
		if(SDL_Flip(screen) < 0) {
			fprintf(stderr, "Unable to flip surfaces: %s\n", SDL_GetError());
			exit(1);
		}

	}
private:
	void put_pixel32( SDL_Surface *surface, int x, int y, Uint32 pixel ) {
		Uint32 *pixels = (Uint32 *)surface->pixels;
		pixels[ ( y * surface->w ) + x ] = pixel;
	} 
};

int main()
{
	Display * display = new SDLDisplay();

	srand(time(NULL));

	Life *life = newLife(display->width(), display->height());
	bigBang(life);
	while(!display->quit()) {
		display->prepareOutput();
		for(int x = 0; x < life->width; x++) {
			for(int y = 0; y < life->height; y++) {
				display->output(x, y, life->map[x + y * life->width]);
			}
		}
		display->doneOutput();

		tick(life);
	}
	freeLife(life);

	delete display;
	return 0;
}
