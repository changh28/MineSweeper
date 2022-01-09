/*
 ============================================================================
 Name        : MineSweeper.c
 Author      : CHX
 Copyright   : THIS PROJECT MUST NOT BE COPIED WITHOUT AUTHORIZATION
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include "MineBlock.h"

typedef struct {
	int row;
	int column;
	int blockNum;
	mineBlock* map;
} mineMap;

mineMap mapInit(int m, int n){ // create an m*n block
	int blockNum = m*n;
	mineBlock* blocks = (mineBlock*)malloc(blockNum*sizeof(mineBlock));
	for(int i = 0; i < blockNum; i++){
		blocks[i] = blockInit(0,0,2);
		// no mine after initialization
		// all blocks are initialized to invisible
	}
	mineMap newMap = {m, n, blockNum, blocks};
	return newMap;
}

void setMine(mineMap emptyMap, int totalMine){
	if(totalMine > emptyMap.blockNum){
		printf("Error: Total number of mines exceeds limit\n");
	}else{
		int i = 0;
		while(i < totalMine){
			int pos = rand() % emptyMap.blockNum; // random position within [0, blockNum-1]
			if((emptyMap.map[pos]).mineNum != 1){ // the block is NOT taken up
				(emptyMap.map[pos]).mineNum = 1; // mine set
				i++;
			}
		}
	}
}

int getX(mineMap target, int pos){
	int X;
	if(pos < 0 || pos >= target.blockNum){
		X = -1;
		printf("Error: Invalid position outside map\n");
	}else{
		X = pos % target.column; // X within [0, column-1]
	}
	return X;
}

int getY(mineMap target, int pos){
	int Y;
	if(pos < 0 || pos >= target.blockNum){
		Y = -1;
		printf("Error: Invalid position outside map\n");
	}else{
		Y = pos / target.column; // Y within [0, row-1]
	}
	return Y;
}

void countMine(mineMap halfMap){
	for(int i = 0; i < halfMap.blockNum; i++){
		if(getY(halfMap, i) == 0){ // upper bound
			if(getX(halfMap, i) == 0){ // left up corner
				(halfMap.map[i]).dispNum = (halfMap.map[i+halfMap.column]).mineNum\
				+ (halfMap.map[i+1]).mineNum + (halfMap.map[i+1+halfMap.column]).mineNum;
			}else if(getX(halfMap, i) == halfMap.column-1){ // right up corner
				(halfMap.map[i]).dispNum = (halfMap.map[i+halfMap.column]).mineNum\
				+ (halfMap.map[i-1]).mineNum + (halfMap.map[i-1+halfMap.column]).mineNum;
			}else{
				(halfMap.map[i]).dispNum = (halfMap.map[i+halfMap.column]).mineNum\
				+ (halfMap.map[i-1]).mineNum + (halfMap.map[i-1+halfMap.column]).mineNum\
				+ (halfMap.map[i+1]).mineNum + (halfMap.map[i+1+halfMap.column]).mineNum;
			}
		}else if(getY(halfMap, i) == halfMap.row-1){ // lower bound
			if(getX(halfMap, i) == 0){ // left down corner
				(halfMap.map[i]).dispNum = (halfMap.map[i-halfMap.column]).mineNum\
				+ (halfMap.map[i+1]).mineNum + (halfMap.map[i+1-halfMap.column]).mineNum;
			}else if(getX(halfMap, i) == halfMap.column-1){ // right down corner
				(halfMap.map[i]).dispNum = (halfMap.map[i-halfMap.column]).mineNum\
				+ (halfMap.map[i-1]).mineNum + (halfMap.map[i-1-halfMap.column]).mineNum;
			}else{
				(halfMap.map[i]).dispNum = (halfMap.map[i-halfMap.column]).mineNum\
				+ (halfMap.map[i-1]).mineNum + (halfMap.map[i-1-halfMap.column]).mineNum\
				+ (halfMap.map[i+1]).mineNum + (halfMap.map[i+1-halfMap.column]).mineNum;
			}
		}else if(getX(halfMap, i) == 0){ // left bound
			(halfMap.map[i]).dispNum = (halfMap.map[i-halfMap.column]).mineNum + (halfMap.map[i+halfMap.column]).mineNum\
			+ (halfMap.map[i+1]).mineNum + (halfMap.map[i+1-halfMap.column]).mineNum + (halfMap.map[i+1+halfMap.column]).mineNum;
		}else if(getX(halfMap, i) == halfMap.column-1){ // right bound
			(halfMap.map[i]).dispNum = (halfMap.map[i-halfMap.column]).mineNum + (halfMap.map[i+halfMap.column]).mineNum\
			+ (halfMap.map[i-1]).mineNum + (halfMap.map[i-1-halfMap.column]).mineNum + (halfMap.map[i-1+halfMap.column]).mineNum;
		}else{ // general cases
			(halfMap.map[i]).dispNum = (halfMap.map[i-halfMap.column]).mineNum + (halfMap.map[i+halfMap.column]).mineNum\
			+ (halfMap.map[i-1]).mineNum + (halfMap.map[i-1-halfMap.column]).mineNum + (halfMap.map[i-1+halfMap.column]).mineNum\
			+ (halfMap.map[i+1]).mineNum + (halfMap.map[i+1-halfMap.column]).mineNum + (halfMap.map[i+1+halfMap.column]).mineNum;
		}
	}
}



int main(void) {
	mineMap a = mapInit(9,9);
	setMine(a,30);
	countMine(a);
	for(int i = 0; i < a.blockNum; i++){
		printf("%c ",(a.map[i].mineNum==0)? '0' : '*');
		if((i+1)%9==0){
			printf("\n");
		}
	}
	printf("\n");
	for(int i = 0; i < a.blockNum; i++){
		printf("%d ",a.map[i].dispNum);
		if((i+1)%9==0){
					printf("\n");
		}
	}
	return 0;
}
