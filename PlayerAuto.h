#pragma once

#include "PlayerBase.h"
#include "ILevelStrategy.h"
#include "GameConst.h"

class CPlayerAuto: public CPlayerBase
{
public:
	CPlayerAuto(PLAYER_LEVEL_e a_playerLevel);

	virtual void PlayTurn(const GAME_STATUS& gameState);

private:
	PLAYER_LEVEL_e m_level;
	ILevelStrategy* m_levelStartegy;
};

