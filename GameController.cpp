#include "GameController.h"
#include <iostream>

CGameController::CGameController()
{
	m_registerIdx = 0;
	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		m_registeredObservers[i] = NULL;
	}
}

void CGameController::SetPlayers(CPlayerBase* a_player1, CPlayerBase* a_player2)
{
	m_player1 = a_player1;
	m_player1->SetPlayTurnCmd(m_PlayTurnAckCmd);
	
	m_player2 = a_player2;
	m_player1->SetPlayTurnCmd(m_PlayTurnAckCmd);
}

void CGameController::SetInitAckCmd(CInitAckCmd* a_cmd)
{
	m_InitAckCmd = a_cmd;
}

void CGameController::SetPlayTurnAckCmd(CPlayTurnAckCmd* a_cmd)
{
	m_PlayTurnAckCmd = a_cmd;
}


void CGameController::InitAcknowledge(int numPlayers, PLAYER_LEVEL_e a_gameLevel)
{
	m_InitAckCmd->SetNumPlayers(numPlayers);

	switch (a_gameLevel)
	{
		
	}
	m_InitAckCmd->SetGameLevel();
}

void CGameController::UpdateGameStatus(const GAME_STATUS& a_gameState)
{
	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		m_registeredObservers[i]->Notify(a_gameState);
	}
}


RETCODE_e CGameController::RegisterToSubject(IGameObserver* a_observer)
{
	if (m_registerIdx >= 0 && m_registerIdx < NUM_PLAYERS)
	{
		m_registeredObservers[m_registerIdx] = a_observer;
		m_registerIdx++;
		return OK;
	}

	return NOT_OK;
}
