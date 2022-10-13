#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <time.h>

#define HORIZONTAL 222
#define VERTICAL 41

void initGraph(void);
void printProc(void);
int getDigit(int number, int digit);
void gotoXY(int, int);
void update(int);
void shift(void);
void clear(void);
void putProc(int);

char firstmainbuffer[VERTICAL][HORIZONTAL];
char seccondmainbuffer[VERTICAL][HORIZONTAL];

#endif

