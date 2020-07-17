#pragma once

#include "GameConst.h"
class ILevelStrategy
{
public:
	ILevelStrategy() {};

	virtual int playTurn(const GAME_STATUS& gameState)=0;
};
