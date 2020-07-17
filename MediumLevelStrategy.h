#pragma once

#include "ILevelStrategy.h"

class CMediumLevelStrategy : public ILevelStrategy
{
public:

	CMediumLevelStrategy();

	virtual int playTurn(const GAME_STATUS& gameState);
};

