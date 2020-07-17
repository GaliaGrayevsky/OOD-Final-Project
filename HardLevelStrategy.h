#pragma once

#include "ILevelStrategy.h"

class CHardLevelStrategy : public ILevelStrategy
{
public:

	CHardLevelStrategy();

	virtual int playTurn(const GAME_STATUS& gameState);
};

