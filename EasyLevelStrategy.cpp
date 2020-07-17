#include "EasyLevelStrategy.h"
#include <stdlib.h>  
#include <time.h>

CEasyLevelStrategy::CEasyLevelStrategy()
{
	srand(time(NULL));
}

int CEasyLevelStrategy::playTurn(const GAME_STATUS& a_gameState)
{
	
	int col = rand() % NUM_COL;
	return col;
}
