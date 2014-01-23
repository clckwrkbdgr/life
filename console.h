#pragma once
#include "display.h"

class Ncurses : public Display {
public:
	Ncurses();
	virtual ~Ncurses();
	virtual bool quit() const;
	virtual void prepareOutput();
	virtual void output(int x, int y, int value);
	virtual void doneOutput();
private:
	bool double_width_char;
};

