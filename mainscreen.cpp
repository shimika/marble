#include "function.h"
using namespace std;

static int cursorpos;

void movecursor(int direction) {
	cursorpos = max2(0, cursorpos + direction);
	cursorpos = min2(3, cursorpos);

	gotoxy(0, 0);

	int i;
	for (i = 0; i < 4; i++) {
		gotoxy(8, i * 2 + 4);
		printf("  ");
	}

	gotoxy(8, cursorpos * 2 + 4);
	printf("▶");
}

void printmenu() {
	int i;
	char menutitle[5][21] = { "2 players", "3 players", "4 players", "exit", "\'학고\'대의 마블" };

	for (i = 0; i < 4; i++) {
		gotoxy(12, i * 2 + 4);
		printf("%s", menutitle[i]);
	}

	gotoxy(12, 20);
	printf("%s", menutitle[4]);
}

void mainscreen() {
	system("mode con cols=50 lines=25");
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