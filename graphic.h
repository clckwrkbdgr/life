#pragma once
#include "display.h"
#include <stdint.h>
class SDL_Surface;

class SDLDisplay : public Display {
public:
	static int WIDTH;
	static int HEIGHT;
	enum { CELLSIZE = 5, DELAY = 50, VIDEODEPTH = 32 };
	enum { CELLCOLOR = 0x002f5fff, BKCOLOR = 0 };
	SDL_Surface * screen;
	SDL_Surface * cell;

	SDLDisplay();
	virtual ~SDLDisplay();
	virtual bool quit() const;
	virtual void prepareOutput();
	virtual void output(int x, int y, int value);
	virtual void doneOutput();
private:
	void put_pixel32(SDL_Surface *surface, int x, int y, uint32_t pixel);
};
