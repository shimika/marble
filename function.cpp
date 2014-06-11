#include <Windows.h>
#include <stdio.h>
#include <string.h>

// ������ �������� ����
void setwindowposition() {
	HWND consoleWindow = GetConsoleWindow();
	SetWindowPos(consoleWindow, 0, 50, 70, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

// Ŀ���� Ư�� ��ġ�� ����
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

// �ܼ� ���� ���� ����
void settextcolor(int col) {
	HANDLE hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	FlushConsoleInputBuffer(hStdOutput);
	SetConsoleTextAttribute(hStdOutput, col);
}

// �����̴� Ŀ���� ����
void hidecursor() {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);
}

// Ư�� ��ġ�� ��Ʈ���� ���
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