#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "function.h"

int nPlayer;

int main() {
	system("mode con cols=150 lines=40");

	hidecursor();
	mainscreen();

	system("cls");
	printf("%d\n", nPlayer);
	return 0;
}
