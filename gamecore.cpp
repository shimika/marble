#include "function.h"

int nPlayer;

int main() {
	srand(time(0));


	setwindowposition();
	hidecursor();
	mainscreen();

	selectrandom();
	printgamescreen();

	play();

	resultscreen();

	return 0;
}
