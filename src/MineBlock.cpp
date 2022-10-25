
#include "MineBlock.h"

mineBlock blockInit(int selfMine, int mineAmount, int blockStatus){
	
	mineBlock newBlock = {selfMine, mineAmount, blockStatus};
	return newBlock;
}
