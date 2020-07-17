#pragma once

#include "PlayerBase.h"


class CPlayerManual : public CPlayerBase
{
public:
	CPlayerManual();

	virtual void PlayTurn(const GAME_STATUS& gameState);

private:
	
};




