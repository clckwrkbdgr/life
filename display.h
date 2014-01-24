#pragma once
class Life;

class Display {
public:
	Display() : w(0), h(0) {}
	virtual ~Display() {}

	int width() const { return w; }
	int height() const { return h; }
	void setWidth(int value) { w = value; }
	void setHeight(int value) { h = value; }

	virtual bool quit() const = 0;
	virtual void output(const Life & life) = 0;
private:
	int w, h;
};

