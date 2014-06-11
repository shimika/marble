#include <Windows.h>
#include <stdio.h>
#include <string.h>

// 윈도우 포지션을 설정
void setwindowposition() {
	HWND consoleWindow = GetConsoleWindow();
	SetWindowPos(consoleWindow, 0, 50, 70, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

// 커서를 특정 위치로 설정
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

// 콘솔 문자 색을 설정
void settextcolor(int col) {
	HANDLE hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	FlushConsoleInputBuffer(hStdOutput);
	SetConsoleTextAttribute(hStdOutput, col);
}

// 깜빡이는 커서를 삭제
void hidecursor() {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);
}

// 특정 위치에 스트링을 출력
void printscreen(char *str, int x, int y) {
	int i, len = strlen(str), height = y;

	gotoxy(x, y);

	for (i = 0; i < len; i++) {
		if (str[i] == 10) {
			gotoxy(x, ++y);
		}
		else {
			printf("%c", str[i]);
		}
	}
}