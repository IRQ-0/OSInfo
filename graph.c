#include "graph.h"

void putProc(int proc) {
	update(proc);
	shift();
}

void clear(void) {
	for (int i = 0; i < VERTICAL; i++) {
		for (int j = 0; j < HORIZONTAL; j++) {
			firstmainbuffer[i][j] = ' ';
		}
	}
	printProc();
}

void update(int in) {
	if (in == 100) {
		for (int i = 0; i < VERTICAL; i++)
			firstmainbuffer[i][0] = '#';
		printProc();
		return;
	} else if (in == 0) {
		for (int i = 40; i < VERTICAL; i++)
			firstmainbuffer[i][0] = '#';
		printProc();
		return;
	 } else if ((in % 10) == 0) {
	 	for (int i = (((10 - getDigit(in, 1)) * 4)); i < VERTICAL; i++)
			firstmainbuffer[i][0] = '#';
		printProc();
		return;
	 } else if (getDigit(in, 0) < 5) {
	 	for (int i = (((10 - getDigit(in, 1)) * 4) - 1); i < VERTICAL; i++)
			firstmainbuffer[i][0] = '#';
		printProc();
		return;
	 } else if (getDigit(in, 0) > 5) {
	 	for (int i = (((10 - getDigit(in, 1)) * 4) - 3); i < VERTICAL; i++)
			firstmainbuffer[i][0] = '#';
		printProc();
		return;
	 } else if (in % 5 == 0 && in % 10 != 0) {
	 	for (int i = (((10 - getDigit(in, 1)) * 4) - 2); i < VERTICAL; i++)
			firstmainbuffer[i][0] = '#';
		printProc();
		return;
	 }
}

void shift(void) {
	for (int i = 0; i < VERTICAL; i++) {
		for (int j = 0; j < HORIZONTAL; j++) {
			seccondmainbuffer[i][j] = ' ';
		}
	}
	for (int i = 0; i < VERTICAL; i++) {
		for (int j = 0; j < (HORIZONTAL - 1); j++) {
			seccondmainbuffer[i][j + 1] = firstmainbuffer[i][j];
		}
	}
	for (int i = 0; i < VERTICAL; i++) {
		for (int j = 0; j < HORIZONTAL; j++) {
			firstmainbuffer[i][j] = seccondmainbuffer[i][j];
		}
	}
	printProc();
}

void gotoXY(int x, int y) {
   COORD p;
   p.X = x - 1;
   p.Y = y - 1;
   HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleCursorPosition(hconsole, p);
}

int getDigit(int number, int digit) {
   return (number / ((int) pow(10, digit)) % 10);
}

void printProc(void) {
	gotoXY(8, 2);
	for (int i = 0; i < VERTICAL; i++) {
		gotoXY(8, 2 + i);
		for (int j = 0; j < HORIZONTAL; j++) {
			putchar(firstmainbuffer[i][j]);
		}
	}
}

void initGraph(void) {
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
	system("mode 650");
	system("cls");
	for (int i = 100; i >= 0; i -= 5) {
		puts("");
		printf("  %d%%  \n", i);
	}
	puts("\n\n  Press CTRL+C to stop");
	clear();
	
}

