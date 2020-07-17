#pragma once

#include "GameConst.h"
#include "PlayTurnAckCmd.h"

class CPlayerBase
{
public:
	CPlayerBase();

	RETCODE_e InitPlayer(PLAYER_e a_player);
	void SetPlayTurnCmd(CPlayTurnAckCmd* a_cmd);


protected:

	virtual void PlayTurn(const GAME_STATUS& a_gameState) = 0;
	void BuildPlayCmd(int a_dstColumn);
	RETCODE_e CheckPlayValidity(const GAME_STATUS& a_gameState, int a_colToPutDisc);

	PLAYER_e m_player;
	CPlayTurnAckCmd* m_playCmd;
	
};

