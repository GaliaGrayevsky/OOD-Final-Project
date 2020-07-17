#pragma once

#include "ILevelStrategy.h"

class CEasyLevelStrategy : public ILevelStrategy
{
public:

	CEasyLevelStrategy();

	virtual int playTurn(const GAME_STATUS& gameState);
};

