#pragma once

#include "GameConst.h"

class IGameObserver
{
public:
	IGameObserver() {};

	virtual void Notify(const GAME_STATUS& gameState) = 0;
};
