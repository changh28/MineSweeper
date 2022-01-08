/*
 * MineBlock.c
 *
 *  Created on: Dec 24, 2021
 *      Author: CHX
 */

#include "MineBlock.h"

typedef struct {
	int mineNum; //the amount of mine, 0 or 1
	int dispNum; //displayed sum of mines within 3*3 block(general cases)
	int status;
	/*
	0 -> flag;
	1 -> visible;
	2 -> invisible
	*/
} mineBlock;

mineBlock blockInit(int selfMine, int mineAmount, int blockStatus){
	mineBlock newBlock = {selfMine, mineAmount, blockStatus};
	return newBlock;
}
