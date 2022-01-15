/*
 ================================================================================
 Name        : MineBlock.cpp
 Author      : CHX
 Copyright   : This project must NOT be copied or shared without authorization
 ================================================================================
 */

#include "MineBlock.h"

mineBlock blockInit(int selfMine, int mineAmount, int blockStatus){
	mineBlock newBlock = {selfMine, mineAmount, blockStatus};
	return newBlock;
}
