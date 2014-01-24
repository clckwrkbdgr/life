#include "life.h"
#include "console.h"
#include <ctime>
#include <cstdlib>

int main(int /*argc*/, char ** /*argv*/)
{
	srand(time(NULL));
	Ncurses display;
	Life life(display.width(), display.height());
	life.bigBang();
	while(!display.quit()) {
		display.output(life);
		life.tick();
	}
	return 0;
}
