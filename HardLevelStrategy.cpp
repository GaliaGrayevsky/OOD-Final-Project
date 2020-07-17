#include "HardLevelStrategy.h"

#include <stdlib.h>  

CHardLevelStrategy::CHardLevelStrategy()
{
}

int CHardLevelStrategy::playTurn(const GAME_STATUS& a_gameState)
{
	int col = rand() % NUM_COL;
	return col;
}