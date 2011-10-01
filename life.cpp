#include <cstdlib>

#include "life.h"

struct Life::Data
{
	int width,height,depth,raceCount;
	Cell **map; // 0 is for dead, any other is for alive (in their own way).
	unsigned int *hashes; // As long as layer depth.
	bool born[8],stayAlive[8];


	Data(int newWidth,int newHeight,int newDepth,int newRaceCount)
		: width(newWidth),height(newHeight),depth(newDepth),raceCount(newRaceCount),
		map(0),hashes(new unsigned int[depth])
	{
		map = new Cell*[depth];
		for(int i=0;i<depth;i++)
			map[i] = new Cell[width * height];

		for(int i=0;i<8;i++)
			born[i] = stayAlive[i] = false;

		// Apply life rule B3/S23.
		born[3] = true;
		stayAlive[2] = stayAlive[3] = true;
	}


	~Data()
	{
		for(int i=0;i<depth;i++)
			delete []map[i];
		delete []map;
		delete []hashes;
	}


	Cell& cell(int layer,int x,int y)
	{
		return map[layer][x + y * width];
	}


	uint topLayerHash()
	{
		unsigned int h=0;
		unsigned int g;

		for(int x=0;x<width;x++)
			for(int y=0;y<height;y++)
			{
				h = (h<<4) + cell(depth-1, x, y);

				if((g=(h&0xf0000000)) != 0)
					h^=g>>23;
				h&=~g;
			}

		return h;
	}
};


//--------------------------------------------------------------------------------------------------


Life::Life(int newWidth,int newHeight,int newDepth,int newRaceCount)
	: d(new Data(newWidth,newHeight,newDepth,newRaceCount))
{
	bigBang();
}


Life::~Life()
{
	delete d;
}


int Life::depth()
{
	return d->depth;
}


int Life::width()
{
	return d->width;
}


int Life::height()
{
	return d->height;
}


int Life::raceCount()
{
	return d->raceCount;
}


Cell Life::cell(int x,int y,int layer)
{
	return d->cell(layer, x, y);
}


void Life::bigBang()
{
	for(int x=0;x<d->width;x++)
		for(int y=0;y<d->height;y++)
			d->cell(d->depth-1,x,y) = rand() % (d->raceCount + 1);
}


bool Life::tick()
{
	// Layer == 0 is buffer.
	// Layer == depth-1 is outputting on screen.

	for(int x=0;x<d->width;x++)
		for(int y=0;y<d->height;y++)
		{
			//get neighbours
			int top=((y<=0)?(d->height-1):(y-1)),
				bottom=((y>=d->height-1)?(0):(y+1)),
				left=((x<=0)?(d->width-1):(x-1)),
				right=((x>=d->width-1)?(0):(x+1));
			Cell neighbours[8]={
				d->cell(d->depth-1,left, top),
				d->cell(d->depth-1,x,top),
				d->cell(d->depth-1,right,top),
				d->cell(d->depth-1,right,y),
				d->cell(d->depth-1,right,bottom),
				d->cell(d->depth-1,x,bottom),
				d->cell(d->depth-1,left,bottom),
				d->cell(d->depth-1,left,y)};
			Cell frequency[8]={0,0,0,0,0,0,0,0};

			// Get neighbours count and frequency.
			int neighboursCount=0;
			int maxIndex=0;
			for(int i=0;i<8;i++)
			{
				for(int j=0;j<8;j++)
					if(neighbours[i]!=0 && neighbours[i]==neighbours[j])
					{
						frequency[j]++;

						// Get max frequent cell value
						if(frequency[maxIndex]<frequency[j])
							maxIndex=j;
					}

				if(neighbours[i]!=0) neighboursCount++;
			}

			// Process cells.
			if(d->cell(d->depth-1,x,y)==0)
			{
				if(d->born[neighboursCount]) // Is born.
					d->cell(0,x,y)=neighbours[maxIndex];
				else
					d->cell(0,x,y)=0; // Stays dead.
			}
			else
			{
				if(d->stayAlive[neighboursCount]) // Stays alive.
					d->cell(0,x,y)=d->cell(d->depth-1,x,y);
				else
					d->cell(0,x,y)=0; // Is died.
			}
		}

	// Swap layers.
	Cell *tmp=d->map[0]; // Buffer.
	uint currentHash=d->topLayerHash();
	bool explodeNewLife=false; // Game is stuck. Nothing new is going to happen. So let's explode new Big Bang.

	for(int i=0;i<d->depth-1;i++)
	{
		d->map[i]=d->map[i+1];

		if(d->hashes[i]==currentHash) // There was already the same map before.
			explodeNewLife=true;
		d->hashes[i]=d->hashes[i+1];
	}

	d->map[d->depth-1]=tmp;
	d->hashes[d->depth-1]=currentHash;

	return !explodeNewLife;
}
