/*
 * windowlist.h
 *
 *  Created on: Jan 1, 2014
 *      Author: cody
 */

#ifndef WINDOWLIST_H_
#define WINDOWLIST_H_

#include "common.h"
#include <ncurses.h>

enum winFlags { TitleOff = 1, LabelOff = 1<<1, GridOff = 1<<2, ExpandedTitleOff = 1<<3, BorderOff = 1<<4 };
enum winType { PercentChart };
enum winDataType { CPUData, MemData, NetData };

enum lineDir { HORIZ, VERT };

struct windowlist
{
	struct windowlist* next;
	WINDOW* titlewin;
	WINDOW* contentwin;
	WINDOW* labelwin;
	char title[25];
	int flags;
	enum winType type;
	struct GRect frame;
	struct arrowPointers
	{
		struct windowlist* left;
		struct windowlist* right;
		struct windowlist* up;
		struct windowlist* down;
	} surrounding;
	enum winDataType dataType;
	int dataSource;
	float* data;
	int dataLen;
};

//void dataSourceChanged(struct windowlist* win);
void drawScreen(struct windowlist* win);
void remapArrows(struct windowlist* wins, struct windowlist* win);
void resizeWindowToFrame(struct windowlist* win);
void splitV(struct windowlist* old);
void splitH(struct windowlist* old);
//void writeAllRefresh(struct windowlist* list);
void refreshAll(struct windowlist* wins, struct windowlist* focus);
void printLine(int row, int col, enum lineDir direction, int len);
struct windowlist* addWin(struct windowlist** wins);
void freeWin(struct windowlist** wins, struct windowlist* win);

#endif /* WINDOWLIST_H_ */