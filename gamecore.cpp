#include "function.h"

int nPlayer;

int main() {
	srand(time(0));


	setwindowposition();
	hidecursor();
	mainscreen();

	selectrandom();
	printgamescreen();

	resultscreen();
	return 0;

	play();

	resultscreen();

	return 0;
}
