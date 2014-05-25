#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "function.h"

static int cursorpos;

void movecursor(int direction) {
	cursorpos = max2(0, cursorpos + direction);
	cursorpos = min2(3, cursorpos);

	gotoxy(0, 0);

	int i;
	for (i = 0; i < 4; i++) {
		gotoxy(11, i * 2 + 8);
		printf("  ");
	}

	gotoxy(11, cursorpos * 2 + 8);
	printf("¢º");
}

void printmenu() {
	int i;
	char menutitle[4][11] = { { "2 players" }, { "3 players" }, { "4 playes" }, { "exit" } };

	for (i = 0; i < 4; i++) {
		gotoxy(15, i * 2 + 8);
		printf("%s", menutitle[i]);
	}
}

void mainscreen() {
	system("cls");
	cursorpos = 0;

	printmenu();
	movecursor(0);

	unsigned char key;
	while (1) {
		key = getch();

		//for detect the arrow keys 
		//we must call the getch() again
		//testing if a is '0' or '0xE0'

		if (key == 0 || key == 0xE0) {
			key = getch();
		}

		switch (key) {
			// Enter key
			case 13:
			case 10:
				// if player is 2 ~ 4 (pos 0 ~ 2)
				if (cursorpos <= 2) {
					nPlayer = cursorpos + 2;
					return;
				}
				else {
					exit(0);
				}
				break;

			// up arrow
			case 72:
				movecursor(-1);
				break;
			// down arrow
			case 80:
				movecursor(1);
				break;
		}
	}
}