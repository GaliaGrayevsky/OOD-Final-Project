#include "GameConsuleView.h"
#include <iostream>

CGameConsuleView::CGameConsuleView()
{
}

void CGameConsuleView::InitConsuleView(CGameController* a_controller)
{
	m_controller = a_controller;
	m_controller->RegisterToSubject(this);
}

void CGameConsuleView::Notify(const GAME_STATUS& a_gameState)
{
	switch (a_gameState.state)
	{
	case INIT_STATE:
		DisplayInit();
		break;
	case PLAY_TURN_STATE:
		break;
	case WIN_GAME_STATE:
		break;
	case END_GAME_STATE:
		break;
	
	default:
		break;
	}
}

void CGameConsuleView::DisplayInit()
{
	int gameConfiguration = 0;
	int numManPlayers = 0;
	PLAYER_LEVEL_e gameLevel = 0;

	printf("\n---- ------------------------ ----\n");
	printf("\n---- Welcome To Four In A Raw ----\n");
	do
	{
		printf("\n---- Choose Game Configuration (1/2/3):\n");
		printf("\n---- 1. Play Against Auto Player.");
		printf("\n---- 2. Play Against A Friend.");
		printf("\n---- 3. Watch 2 Auto Players Playing.");

		scanf_s("%d", &gameConfiguration);

	}while(gameConfiguration!=1 && gameConfiguration != 2 && gameConfiguration != 3);

	if (gameConfiguration == 1 || gameConfiguration == 3)
	
	do
	{
		printf("\n---- Choose Game Level (0/1/2):");
		printf("\n---- 0. Easy.");
		printf("\n---- 1. Medium.");
		printf("\n---- 2. Hard.");
		scanf_s("%d", &gameLevel);
	} while (gameLevel!=1 && gameLevel!=2 && gameLevel!=3);
	
	switch (gameConfiguration)
	{
	case 1:
		numManPlayers = 1;
		break;
	case 2:
		numManPlayers = 2;
		break;
	case 3:
		numManPlayers = 0;
		break;
	}
	printf("\n ---- Starting game with %d players ---- \n", numManPlayers);
	printf("\n---- ------------------------ ----\n");

	m_controller->InitAcknowledge(numManPlayers, gameLevel);
}

void CGameConsuleView::DisplayPlayTurn(const GAME_STATUS& a_gameState)
{
}

void CGameConsuleView::DisplayWinGame(const GAME_STATUS& a_gameState)
{
}

void CGameConsuleView::DisplayEndGame()
{
}


