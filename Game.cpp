#include "Game.h"
#include <iostream>
#include "InitGameState.h"
#include "PlayTurnGameState.h"
#include "CheckGameState.h"
#include "EndGameState.h"

CGame::CGame()
{
	m_semaphore = new CSemaphore();
	
	m_gameState[INIT_STATE] = new CInitGameState();
	m_gameState[PLAY_TURN_STATE] = new CPlayTurnGameState();
	m_gameState[CHECK_GAME_STATE] = new CCheckGameState();
	m_gameState[WIN_GAME_STATE] = new CEndGameState();
	m_gameState[END_GAME_STATE] = new CEndGameState();

	m_player1 = NULL;
	m_player2 = NULL;
}

void CGame::InitGame(CGameController* a_gameController)
{
	m_gameController = a_gameController;
}

void CGame::InitGameUpdate()
{
	GAME_STATUS gameStatus;
	BuildGameStatus(gameStatus);
	// Notify GameController
	m_gameController->UpdateGameStatus(gameStatus);
}

int CGame::PlayAGame()
{
	// Init Board
	m_board.InitBoard();

	SetState(INIT_STATE);

	while(m_currentState != END_GAME_STATE)
	{
		m_gameState[m_currentState]->HandleStateActivity(this);
	}
	
	printf("DBG: Ended game!\n");

	return 0;
}



void CGame::ExecuteTurn(PLAYER_e a_player, int a_dstCol)
{
	CDisc* disc = new CDisc();
	disc->SetDiscParams(a_player);
	m_board.SetDiscInPlace(*disc, a_dstCol);

	m_semaphore->notify();
}

void CGame::BuildGameStatus(GAME_STATUS& a_gameStatus)
{
	a_gameStatus.state = m_currentState;
	m_board.GetBoardState(a_gameStatus.bord);
	a_gameStatus.colorTurn = m_currentPlayerTurn;
}

void CGame::SetState(GAME_STATE_e a_gameState)
{
	m_currentState = a_gameState;
}

bool CGame::CheckIsThereAWinner()
{
	bool WinnerFound = false;
	PLAYER_e WinningPlayer;
	BOARD_SNAPSHOT board;
	int a_startRaw = 0;
	int a_endRaw = 0;
	int a_startCol = 0;
	int a_endCol = 0;

	m_board.GetBoardState(board);
	
	for (int rawIdx = 0; rawIdx < NUM_RAW; rawIdx++)
	{
		// Check Raws
		if (WinnerFound = CheckOneRaw(board, rawIdx, 0, RAW, WinningPlayer, a_startRaw, a_endRaw, a_startCol, a_endCol) == true)
			break;

		// Check Left Diagonals
		if (rawIdx > 2)
		{
			if (WinnerFound = CheckOneRaw(board, rawIdx, 0, DIAG_LEFT, WinningPlayer, a_startRaw, a_endRaw, a_startCol, a_endCol) == true)
				break;
		}

		// Check Right Diagonals
		if (rawIdx < 3)
		{
			if (WinnerFound = CheckOneRaw(board, rawIdx, 0, DIAG_RIGHT, WinningPlayer, a_startRaw, a_endRaw, a_startCol, a_endCol) == true)
				break;
		}
	}

	if (false == WinnerFound)
	{
		for (int colIdx = 0; colIdx < NUM_COL; colIdx++)
		{
			// Check Columns
			if (WinnerFound = CheckOneRaw(board, 0, colIdx, COL, WinningPlayer, a_startRaw, a_endRaw, a_startCol, a_endCol) == true)
				break;

			// Check Left Diagonals
			if (colIdx < 4)
			{
				if (WinnerFound = CheckOneRaw(board, NUM_RAW - 1, colIdx, DIAG_LEFT, WinningPlayer, a_startRaw, a_endRaw, a_startCol, a_endCol) == true)
					break;
			}

			// Check Right Diagonals
			if (colIdx < 4)
			{
				if (WinnerFound = CheckOneRaw(board, 0, colIdx, DIAG_RIGHT, WinningPlayer, a_startRaw, a_endRaw, a_startCol, a_endCol) == true)
					break;
			}
		}
	}

	return WinnerFound;
}

bool CGame::CheckOneRaw(BOARD_SNAPSHOT& a_bord, int a_raw, int a_col, ORIENTATION_e a_orientation, PLAYER_e& a_color,
	int& a_startRaw, int& a_endRaw, int& a_startCol, int& a_endCol)
{
	int ColStep = 0;
	int RawStep = 0;
	int maxCol = 0;
	int maxRaw = 0;

	switch (a_orientation)
	{
	case RAW:
		RawStep = 0;
		maxRaw = a_raw+1;
		ColStep = 1;
		maxCol = NUM_COL;
		break;
	case COL:
		RawStep = 1;
		maxRaw = NUM_RAW;
		ColStep = 0;
		maxCol = a_col+1;
		break;
	case DIAG_LEFT:
		RawStep = -1;
		maxRaw = 0;
		ColStep = 1;
		maxCol = NUM_COL;
		break;
	case DIAG_RIGHT:
		RawStep = 1;
		maxRaw = NUM_RAW;
		ColStep = 1;
		maxCol = NUM_COL;
		break;
	}

	int counter = 0;
	PLAYER_e currentPlayer;
	int rawIdx = a_raw;
	int colIdx = a_col;
	while (rawIdx != maxRaw && colIdx != maxCol)
	{
		if (true == a_bord.disc[rawIdx][colIdx].taken)
		{
			if (counter == 0)
			{
				currentPlayer = a_bord.disc[rawIdx][colIdx].player;
				a_startRaw = rawIdx;
				a_startCol = colIdx;
				counter++;
			}
			else
			{
				if (currentPlayer == a_bord.disc[rawIdx][colIdx].player)
				{
					counter++;
				}
				else
				{
					currentPlayer = a_bord.disc[rawIdx][colIdx].player;
					counter = 1;
					a_startRaw = rawIdx;
					a_startCol = colIdx;
				}

				if (counter == 4)
				{
					a_color = currentPlayer;
					a_endRaw = rawIdx;
					a_endCol = colIdx;

					printf("\n  ####   WE HAVE A WINNER!!!  %s IS THE WINNER!!!  ####  \n",
						currentPlayer == PLAYER1 ? "PLAYER1" : "PLAYER2");

					printf("\n  ####   Index (%d,%d)-(%d,%d)  ####  \n",
						a_startRaw, a_startCol, a_endRaw, a_endCol);
					return true;
				}
			}
		}
		else
		{
			counter = 0;
		}

		rawIdx += RawStep;
		colIdx += ColStep;
	}
	

	return false;
}

void CGame::InitGameAck(int m_numManPlayers, PLAYER_LEVEL_e a_gameLevel)
{
	switch (m_numManPlayers)
	{
	case 0:
		CPlayerAuto * playerAuto1 = new CPlayerAuto(a_gameLevel);
		playerAuto1->InitPlayer(PLAYER1);

		CPlayerAuto* playerAuto2 = new CPlayerAuto(a_gameLevel);
		playerAuto2->InitPlayer(PLAYER2);

		m_gameController->SetPlayers(playerAuto1, playerAuto2);
		break;
	case 1:
		CPlayerManual* playerMan1 = new CPlayerManual();
		playerMan1->InitPlayer(PLAYER1);

		CPlayerAuto* playerAuto1 = new CPlayerAuto(a_gameLevel);
		playerAuto1->InitPlayer(PLAYER2);

		m_gameController->SetPlayers(playerMan1, playerAuto1);
		break;
	case 2:
		CPlayerManual * playerMan1 = new CPlayerManual();
		playerMan1->InitPlayer(PLAYER1);

		CPlayerManual* playerMan2 = new CPlayerManual();
		playerMan2->InitPlayer(PLAYER2);

		m_gameController->SetPlayers(playerMan1, playerMan2);
		break;
	default:
		CPlayerAuto* playerAuto1 = new CPlayerAuto(a_gameLevel);
		playerAuto1->InitPlayer(PLAYER1);

		CPlayerAuto* playerAuto2 = new CPlayerAuto(a_gameLevel);
		playerAuto2->InitPlayer(PLAYER2);

		m_gameController->SetPlayers(playerAuto1, playerAuto2);
		break;
	}


}


/* OLD OLD 
#include "Game.h"
#include <iostream>
#include "InitGameState.h"
#include "PlayTurnGameState.h"
#include "CheckGameState.h"
#include "EndGameState.h"

CGame::CGame()
{
	m_semaphore = new CSemaphore();

	m_gameState[INIT_STATE] = new CInitGameState();
	m_gameState[PLAY_TURN_STATE] = new CPlayTurnGameState();
	m_gameState[CHECK_GAME_STATE] = new CCheckGameState();
	m_gameState[END_GAME_STATE] = new CEndGameState();

	m_numRegistered = 0;
}

void CGame::InitGame()
{
	// Notify GameController
}

int CGame::PlayAGame()
{
	if (m_numRegistered != MAX_NUM_PLAYERS)
	{
		printf("StartNewGame FAILED. Only %d players registered!", m_numRegistered);
		return NOT_OK;
	}

	// Init Bord
	m_bord.InitBord();
	GAME_STATE gameState;

	// Play turns until one of the players win or the bord is full
	while (false == m_bord.IsBordFull())
	{
		m_bord.GetBordState(gameState.bord);
		gameState.colorTurn = m_currentColorTurn;

		for (int i = 0; i < MAX_NUM_PLAYERS; i++)
		{
			m_registeredObservers[i]->Notify(gameState);
		}

		m_semaphore->wait();

		// Check game after playing
		m_bord.PrintBord(); // TEMP

		if (true == CheckIsThereAWinner())
		{
			// NOTIFY PLAYERS!
			break;
		}

		m_currentColorTurn = COLOR_e((m_currentColorTurn + 1) % NUM_COLORS);
	}

	printf("\n *************GAME OVER***************\n");


	return 0;
}

void CGame::ExecuteTurn(COLOR_e a_color, int a_dstCol)
{
	CDisc* disc = new CDisc();
	disc->SetDiscParams(a_color);
	m_bord.SetDiscInPlace(*disc, a_dstCol);

	m_semaphore->notify();
}

RETCODE_e CGame::RegisterToSubject(IGameObserver* a_observer)
{
	if (m_numRegistered >= 0 && m_numRegistered < MAX_NUM_PLAYERS)
	{
		m_registeredObservers[m_numRegistered] = a_observer;
		m_numRegistered++;
		return OK;
	}

	return NOT_OK;
}

void CGame::SetState(GAME_STATE_e a_gameState)
{
	m_currentState = a_gameState;
}

bool CGame::CheckIsThereAWinner()
{
	bool WinnerFound = false;
	COLOR_e WinningColor;
	BORD_STATE bord;
	int a_startRaw = 0;
	int a_endRaw = 0;
	int a_startCol = 0;
	int a_endCol = 0;

	m_bord.GetBordState(bord);

	for (int rawIdx = 0; rawIdx < NUM_RAW; rawIdx++)
	{
		// Check Raws
		if (WinnerFound = CheckOneRaw(bord, rawIdx, 0, RAW, WinningColor, a_startRaw, a_endRaw, a_startCol, a_endCol) == true)
			break;

		// Check Left Diagonals
		if (rawIdx > 2)
		{
			if (WinnerFound = CheckOneRaw(bord, rawIdx, 0, DIAG_LEFT, WinningColor, a_startRaw, a_endRaw, a_startCol, a_endCol) == true)
				break;
		}

		// Check Right Diagonals
		if (rawIdx < 3)
		{
			if (WinnerFound = CheckOneRaw(bord, rawIdx, 0, DIAG_RIGHT, WinningColor, a_startRaw, a_endRaw, a_startCol, a_endCol) == true)
				break;
		}
	}

	if (false == WinnerFound)
	{
		for (int colIdx = 0; colIdx < NUM_COL; colIdx++)
		{
			// Check Columns
			if (WinnerFound = CheckOneRaw(bord, 0, colIdx, COL, WinningColor, a_startRaw, a_endRaw, a_startCol, a_endCol) == true)
				break;

			// Check Left Diagonals
			if (colIdx < 4)
			{
				if (WinnerFound = CheckOneRaw(bord, NUM_RAW - 1, colIdx, DIAG_LEFT, WinningColor, a_startRaw, a_endRaw, a_startCol, a_endCol) == true)
					break;
			}

			// Check Right Diagonals
			if (colIdx < 4)
			{
				if (WinnerFound = CheckOneRaw(bord, 0, colIdx, DIAG_RIGHT, WinningColor, a_startRaw, a_endRaw, a_startCol, a_endCol) == true)
					break;
			}
		}
	}

	return WinnerFound;
}

bool CGame::CheckOneRaw(BORD_STATE& a_bord, int a_raw, int a_col, ORIENTATION_e a_orientation, COLOR_e& a_color,
	int& a_startRaw, int& a_endRaw, int& a_startCol, int& a_endCol)
{
	int ColStep = 0;
	int RawStep = 0;
	int maxCol = 0;
	int maxRaw = 0;

	switch (a_orientation)
	{
	case RAW:
		RawStep = 0;
		maxRaw = a_raw + 1;
		ColStep = 1;
		maxCol = NUM_COL;
		break;
	case COL:
		RawStep = 1;
		maxRaw = NUM_RAW;
		ColStep = 0;
		maxCol = a_col + 1;
		break;
	case DIAG_LEFT:
		RawStep = -1;
		maxRaw = 0;
		ColStep = 1;
		maxCol = NUM_COL;
		break;
	case DIAG_RIGHT:
		RawStep = 1;
		maxRaw = NUM_RAW;
		ColStep = 1;
		maxCol = NUM_COL;
		break;
	}

	int counter = 0;
	COLOR_e currentColor;
	int rawIdx = a_raw;
	int colIdx = a_col;
	while (rawIdx != maxRaw && colIdx != maxCol)
	{
		if (true == a_bord.disc[rawIdx][colIdx].taken)
		{
			if (counter == 0)
			{
				currentColor = a_bord.disc[rawIdx][colIdx].color;
				a_startRaw = rawIdx;
				a_startCol = colIdx;
				counter++;
			}
			else
			{
				if (currentColor == a_bord.disc[rawIdx][colIdx].color)
				{
					counter++;
				}
				else
				{
					currentColor = a_bord.disc[rawIdx][colIdx].color;
					counter = 1;
					a_startRaw = rawIdx;
					a_startCol = colIdx;
				}

				if (counter == 4)
				{
					a_color = currentColor;
					a_endRaw = rawIdx;
					a_endCol = colIdx;

					printf("\n  ####   WE HAVE A WINNER!!!  %s IS THE WINNER!!!  ####  \n",
						currentColor == BLACK ? "BLACK" : "WHITE");

					printf("\n  ####   Index (%d,%d)-(%d,%d)  ####  \n",
						a_startRaw, a_startCol, a_endRaw, a_endCol);
					return true;
				}
			}
		}
		else
		{
			counter = 0;
		}

		rawIdx += RawStep;
		colIdx += ColStep;
	}


	return false;
}

*/
