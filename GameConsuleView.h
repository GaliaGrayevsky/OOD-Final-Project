#pragma once

#include "IGameObserver.h"
#include "GameController.h"

class CGameConsuleView: public IGameObserver
{
public:
	CGameConsuleView();

	void InitConsuleView(CGameController* a_controller);

	// Implement IGameObserver
	virtual void Notify(const GAME_STATUS& a_gameState);

private:
	void DisplayInit();
	void DisplayPlayTurn(const GAME_STATUS& a_gameState);
	void DisplayWinGame(const GAME_STATUS& a_gameState);
	void DisplayEndGame();

	CGameController* m_controller;
};

