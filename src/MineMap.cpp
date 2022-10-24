
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "../include/MineMap.h"


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

	try{
		if(totalMine > emptyMap.blockNum)
			throw "Error: Total number of mines exceeds limit\n";
	}catch(const char* s){
		std::cerr << s << std::endl;
	}

	int i = 0;
	while(i < totalMine){
		int pos = rand() % emptyMap.blockNum; // random position within [0, blockNum-1]
		if((emptyMap.map[pos]).mineNum != 1){ // the block is NOT taken up
			(emptyMap.map[pos]).mineNum = 1; // mine set
			i++;
		}
	}
}

int getX(mineMap target, int pos){

	int X;
	try{
		if(pos < 0 || pos >= target.blockNum)
			throw "Error: Invalid position outside map\n";
	}catch(const char* s){
		std::cerr << s << std::endl;
	}
	X = pos % target.column; // X within [0, column-1]
	return X;
}

int getY(mineMap target, int pos){

	int Y;
	try{
		if(pos < 0 || pos >= target.blockNum)
			throw "Error: Invalid position outside map\n";
	}catch(const char* s){
		std::cerr << s << std::endl;
	}
	Y = pos / target.column; // Y within [0, row-1]
	return Y;
}

int getPos(mineMap target, int X, int Y){

	int pos;
	try{
		if(X < 0 || X >= target.column || Y < 0 || Y >= target.row)
			throw "Error: Invalid position outside map\n";
	}catch(const char* s){
			std::cerr << s << std::endl;
	}
	pos = X + Y*target.column;
	return pos;
}

void countMine(mineMap halfMap){

	for(int i = 0; i < halfMap.blockNum; i++){
		if(getY(halfMap, i) == 0){ // upper bound

			/** top-left corner
			 * O X
			 * X X
			 */
			if(getX(halfMap, i) == 0){ 
				(halfMap.map[i]).dispNum = 
					(halfMap.map[i + halfMap.column]).mineNum + \
				 	(halfMap.map[i + 1]).mineNum + \
				 	(halfMap.map[i + 1 + halfMap.column]).mineNum;

			/** top-right corner
			 * X O
			 * X X
			 */
			}else if(getX(halfMap, i) == halfMap.column-1){ 
				(halfMap.map[i]).dispNum = 
					(halfMap.map[i + halfMap.column]).mineNum + \
					(halfMap.map[i - 1]).mineNum + \
					(halfMap.map[i - 1 + halfMap.column]).mineNum;

			/** upper bound
			 * X O X
			 * X X X
			 */
			}else{
				(halfMap.map[i]).dispNum = 
					(halfMap.map[i + halfMap.column]).mineNum + \
					(halfMap.map[i - 1]).mineNum + \
					(halfMap.map[i - 1 + halfMap.column]).mineNum + \
					(halfMap.map[i + 1]).mineNum + \
					(halfMap.map[i + 1 + halfMap.column]).mineNum;
			}

		}else if(getY(halfMap, i) == halfMap.row-1){ // lower bound

			/** bottom-left corner
			 * X X
			 * O X
			 */
			if(getX(halfMap, i) == 0){ 
				(halfMap.map[i]).dispNum = 
					(halfMap.map[i - halfMap.column]).mineNum + \
					(halfMap.map[i + 1]).mineNum + \
					(halfMap.map[i + 1 - halfMap.column]).mineNum;
				
			/** bottom-right corner
			 * X X
			 * X O
			 */
			}else if(getX(halfMap, i) == halfMap.column-1){ 
				(halfMap.map[i]).dispNum = 
					(halfMap.map[i - halfMap.column]).mineNum + \
					(halfMap.map[i - 1]).mineNum + \
					(halfMap.map[i - 1 - halfMap.column]).mineNum;
					
			/** lower bound
			 * X X X
			 * X O X
			 */
			}else{
				(halfMap.map[i]).dispNum = 
					(halfMap.map[i - halfMap.column]).mineNum + \
					(halfMap.map[i - 1]).mineNum + \
					(halfMap.map[i - 1 - halfMap.column]).mineNum + \
					(halfMap.map[i + 1]).mineNum + \
					(halfMap.map[i + 1 - halfMap.column]).mineNum;
			}

		/** left bound without corners
		 * X X
		 * O X
		 * X X
		 */
		}else if(getX(halfMap, i) == 0){ 
			(halfMap.map[i]).dispNum = 
				(halfMap.map[i - halfMap.column]).mineNum + \
				(halfMap.map[i + halfMap.column]).mineNum + \
				(halfMap.map[i + 1]).mineNum + \
				(halfMap.map[i + 1 - halfMap.column]).mineNum + \
				(halfMap.map[i + 1 + halfMap.column]).mineNum;

		/** right bound without corners
		 * X X
		 * X O
		 * X X
		 */
		}else if(getX(halfMap, i) == halfMap.column-1){ 
			(halfMap.map[i]).dispNum = 
				(halfMap.map[i - halfMap.column]).mineNum + \
				(halfMap.map[i + halfMap.column]).mineNum + \
				(halfMap.map[i - 1]).mineNum + \
				(halfMap.map[i - 1 - halfMap.column]).mineNum + \
				(halfMap.map[i - 1 + halfMap.column]).mineNum;

		/** central area
		 * X X X
		 * X O X
		 * X X X
		 */
		}else{ 
			(halfMap.map[i]).dispNum = 
				(halfMap.map[i - halfMap.column]).mineNum + \
				(halfMap.map[i + halfMap.column]).mineNum + \
				(halfMap.map[i - 1]).mineNum + \
				(halfMap.map[i - 1 - halfMap.column]).mineNum + \
				(halfMap.map[i - 1 + halfMap.column]).mineNum + \
				(halfMap.map[i + 1]).mineNum + \
				(halfMap.map[i + 1 - halfMap.column]).mineNum + \
				(halfMap.map[i + 1 + halfMap.column]).mineNum;
		}
	}
}

int openCell(mineMap fullMap, int X, int Y){

	int result;
	int pos = getPos(fullMap, X, Y);
	(fullMap.map[pos]).status = 1; // the block become visible

	if((fullMap.map[pos]).mineNum == 1){ // opens a mine
		std::cout << "Game Over\n";
		result = 0;

	}else{
		result = 1;
		if((fullMap.map[pos]).dispNum == 0){ // blank & no mine around the block
			if(X-1 >= 0 && (fullMap.map[getPos(fullMap,X-1,Y)]).status == 2){ // still visible
				openCell(fullMap, X-1, Y); // opens blank blocks to the left
			}
			if(X+1 < fullMap.column && (fullMap.map[getPos(fullMap,X+1,Y)]).status == 2){
				openCell(fullMap, X+1, Y); // opens blank blocks to the right
			}
			if(Y-1 >= 0 && (fullMap.map[getPos(fullMap,X,Y-1)]).status == 2){
				openCell(fullMap, X, Y-1); // opens blank blocks to the top
			}
			if(Y+1 < fullMap.row && (fullMap.map[getPos(fullMap,X,Y+1)]).status == 2){
				openCell(fullMap, X, Y+1); // opens blank blocks to the bottom
			}
		}
	}
	return result;
}

void flagCell(mineMap fullMap, int X, int Y, int act){

	// act: 0 -> undo; 1 -> flag
	int pos = getPos(fullMap, X, Y);
	(fullMap.map[pos]).status = (act) ? 0 : 2;
}

int isFinish(mineMap usedMap){

	int result = 1;

	for(int i = 0; i < usedMap.blockNum; i++){
		if((usedMap.map[i]).mineNum == 0 && (usedMap.map[i]).status == 0){
			result = 0; // incorrectly flagged
		}
		if((usedMap.map[i]).mineNum == 0 && (usedMap.map[i]).status == 2){
			result = 0; // unfinished
		}
	}
	return result;
}

/*
mineMap a = mapInit(9,9);
setMine(a,10);
countMine(a);
int b = click(a,0,8);
int c = isFinish(a);
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
cout << "\n";
for(int i = 0; i < a.blockNum; i++){
	printf("%d ",a.map[i].status);
	if((i+1)%9==0){
		printf("\n");
	}
}
printf("click result = %d\n",b);
printf("if finished = %d\n",c);
*/

