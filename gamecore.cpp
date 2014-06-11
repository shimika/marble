#include "function.h"

int nPlayer;

int main() {
	srand(time(0));

	setwindowposition();
	hidecursor();
	mainscreen();

	selectrandom();
	printgamescreen();

	gotoxy(0, 0);

	play();

	return 0;
}
