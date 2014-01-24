#pragma once
#include "display.h"

class Ncurses : public Display {
public:
	Ncurses();
	virtual ~Ncurses();
	virtual bool quit() const;
	virtual void output(const Life & life);
};

