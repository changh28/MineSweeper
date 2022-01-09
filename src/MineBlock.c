/*
 * MineBlock.c
 *
 *  Created on: Dec 24, 2021
 *      Author: CHX
 */

#include "MineBlock.h"

mineBlock blockInit(int selfMine, int mineAmount, int blockStatus){
	mineBlock newBlock = {selfMine, mineAmount, blockStatus};
	return newBlock;
}
