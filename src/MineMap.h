/*
 ================================================================================
 Name        : MineMap.h
 Author      : CHX
 Copyright   : This project must NOT be copied or shared without authorization
 ================================================================================
 */

#ifndef MINEMAP_H_
#define MINEMAP_H_

#include "MineBlock.h"

typedef struct {
	int row;
	int column;
	int blockNum;
	mineBlock* map;
} mineMap;

mineMap mapInit(int m, int n);
void setMine(mineMap emptyMap, int totalMine);
int getX(mineMap target, int pos);
int getY(mineMap target, int pos);
int getPos(mineMap target, int X, int Y);
void countMine(mineMap halfMap);
int click(mineMap fullMap, int X, int Y);
void flag(mineMap fullMap, int X, int Y, int act);
int isFinish(mineMap usedMap);

#endif /* MINEMAP_H_ */
