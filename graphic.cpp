#include "graphic.h"
#include <SDL/SDL.h>

int SDLDisplay::WIDTH = 1366;
int SDLDisplay::HEIGHT = 768;

SDLDisplay::SDLDisplay()
	: Display(), screen(NULL)
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
		exit(1);
	}
	atexit(SDL_Quit);

	setWidth(WIDTH / CELLSIZE);
	setHeight(HEIGHT / CELLSIZE);
	screen = SDL_SetVideoMode(WIDTH, HEIGHT, VIDEODEPTH, SDL_FULLSCREEN);
	if(!screen) {
		fprintf(stderr, "Unable to set %dx%dx%d video mode: %s\n", WIDTH, HEIGHT, VIDEODEPTH, SDL_GetError());
		exit(1);
	}

	cell = SDL_CreateRGBSurface(0, CELLSIZE, CELLSIZE, VIDEODEPTH, 0, 0, 0, 0);
	SDL_FillRect(cell, NULL, CELLCOLOR);
}

SDLDisplay::~SDLDisplay()
{
	if(cell) {
		SDL_FreeSurface(cell);
	}
	if(screen) {
		SDL_FreeSurface(screen);
	}
}

bool SDLDisplay::quit() const
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_KEYDOWN: return true;
		case SDL_QUIT: return true;
	}
	return false;
}

void SDLDisplay::prepareOutput()
{
	SDL_FillRect(screen, NULL, BKCOLOR);
	if( SDL_MUSTLOCK( screen ) ) {
		SDL_LockSurface( screen );
	} 
}

void SDLDisplay::output(int x, int y, int value)
{
	if(value) {
		SDL_Rect dest;
		dest.x = x * CELLSIZE;
		dest.y = y * CELLSIZE;
		dest.w = CELLSIZE;
		dest.h = CELLSIZE;
		SDL_BlitSurface(cell, NULL, screen, &dest);
	}
}

void SDLDisplay::doneOutput()
{
	if( SDL_MUSTLOCK( screen ) ) {
		SDL_UnlockSurface( screen );
	} 
	if(SDL_Flip(screen) < 0) {
		fprintf(stderr, "Unable to flip surfaces: %s\n", SDL_GetError());
		exit(1);
	}

	SDL_Delay(DELAY);
}

void SDLDisplay::put_pixel32( SDL_Surface *surface, int x, int y, uint32_t pixel ) {
	Uint32 *pixels = (Uint32 *)surface->pixels;
	pixels[ ( y * surface->w ) + x ] = pixel;
} 

