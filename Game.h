#pragma once

#include "IGameContext.h"
#include "IGameState.h"
#include "ICmdReceiver.h"

#include "Board.h"
#include "Semaphore.h"
#include "GameController.h"
#include "PlayerAuto.h"
#include "PlayerManual.h"

class CGame : public IGameContext, ICmdReceiver
{
public:
	CGame();
	void InitGame(CGameController* a_gameController);

	int PlayAGame();

	void ExecuteTurn(PLAYER_e a_color, int a_dstCol);

	// Implement ICmdReceiver
	virtual void InitGameAck(int m_numManPlayers, PLAYER_LEVEL_e a_gameLevel);

	// Implement IContext
	virtual void InitGameUpdate();
	

private:
	void BuildGameStatus(GAME_STATUS& a_gameStatus);
	void SetState(GAME_STATE_e);
	bool CheckIsThereAWinner();
	bool CheckOneRaw(BOARD_SNAPSHOT& a_bord, int a_raw, int a_col, ORIENTATION_e a_orientation, PLAYER_e& a_color,
		int& a_startRaw, int& a_endRaw, int& a_startCol, int& a_endCol);

	CBoard m_board;
	IGameState* m_gameState[NUM_STATES];
	GAME_STATE_e m_currentState;
	CGameController* m_gameController;

	PLAYER_e m_currentPlayerTurn;
	CSemaphore* m_semaphore;
};

