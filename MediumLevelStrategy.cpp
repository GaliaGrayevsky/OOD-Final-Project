#include "MediumLevelStrategy.h"

#include <stdlib.h>  

CMediumLevelStrategy::CMediumLevelStrategy()
{
}

int CMediumLevelStrategy::playTurn(const GAME_STATUS& a_gameState)
{
	int col = rand() % NUM_COL;
	return col;
}

