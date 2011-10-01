#ifndef LIFE_H
#define LIFE_H

typedef unsigned char Cell;

class Life
{
public:
	Life(int newWidth,int newHeight,int newDepth=2,int newRaceCount=1);
	~Life();

	int width();
	int height();
	int depth();
	int raceCount();
	Cell cell(int x,int y,int layer=0); // Knows that map is toroidal
		//layer count from top, e.g. layer 0 is the current, layer 1 is the prev
	void bigBang();
	bool tick(); //returns false when CA enter to inf. loop with period of 2
private:
	struct Data;
	Data *d;

	Life(const Life &other) {}
	Life& operator=(const Life &other) {return *this;}
};

#endif // LIFE_H
