#include <Windows.h>

bool gotoxy(int x, int y) {
	HANDLE hStdOutput;
	COORD cdPos = { x, y };
	hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	if (hStdOutput == INVALID_HANDLE_VALUE) {
		return FALSE;
	}
	SetConsoleCursorPosition(hStdOutput, cdPos);
	return TRUE;
}

void hidecursor() {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);
}
