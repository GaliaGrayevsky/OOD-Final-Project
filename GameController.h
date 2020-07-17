#pragma once

#include "ISubject.h"
#include "GameConst.h"
#include "InitAckCmd.h"
#include "PlayTurnAckCmd.h"
#include "PlayerBase.h"

class CGameController : public ISubject
{
public:
	CGameController();

	void SetPlayers(CPlayerBase* a_player1, CPlayerBase* a_player2);

	void SetInitAckCmd(CInitAckCmd* a_cmd);
	void SetPlayTurnAckCmd(CPlayTurnAckCmd* a_cmd);

	void InitAcknowledge(int numPlayers, PLAYER_LEVEL_e a_gameLevel);

	void UpdateGameStatus(const GAME_STATUS& a_gameState);

	// Implement ISubject
	virtual RETCODE_e RegisterToSubject(IGameObserver* a_observer);

private:
	IGameObserver* m_registeredObservers[NUM_PLAYERS];
	int m_registerIdx;

	CPlayerBase* m_player1;
	CPlayerBase* m_player2;

	CInitAckCmd* m_InitAckCmd;
	CPlayTurnAckCmd* m_PlayTurnAckCmd;
};

