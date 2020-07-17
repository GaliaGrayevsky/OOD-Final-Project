#include "Board.h"
#include <stdio.h>
#include <string.h>

CBoard::CBoard()
{
}

void CBoard::InitBoard()
{
	for (int i = 0; i < NUM_RAW; i++)
	{
		for (int j = 0; j < NUM_COL; j++)
		{
			m_board[i][j] = NULL;
		}
	}
}

RETCODE_e CBoard::SetDiscInPlace(CDisc& a_disc, int a_dstColumn)
{
	RETCODE_e rc = NOT_OK;
	
	for (int i = 0; i < NUM_RAW; i++)
	{
		if (NULL == m_board[i][a_dstColumn])
		{
			m_board[i][a_dstColumn] = &a_disc;
			rc = OK;
			break;
		}
	}
	
	return rc;
}

void CBoard::GetBoardState(BOARD_SNAPSHOT& a_board)
{
	for (int i = 0; i < NUM_RAW; i++)
	{
		for (int j = 0; j < NUM_COL; j++)
		{
			if (NULL != m_board[i][j])
			{
				a_board.disc[i][j].taken = true;
				a_board.disc[i][j].player = m_board[i][j]->GetPlayer();
			}
			else
			{
				a_board.disc[i][j].taken = false;
			}
		}
	}
}

bool CBoard::IsBoardFull()
{
	bool bordFull = true;
	for (int i = 0; i < NUM_RAW; i++)
	{
		for (int j = 0; j < NUM_COL; j++)
		{
			if (NULL == m_board[i][j])
			{
				bordFull = false;
				break;
			}
		}
	}

	return bordFull;
}

void CBoard::PrintBoard()
{
	printf("*************");
	for (int i = NUM_RAW-1; i >=0 ; i--)
	{
		printf("*\n*");
		for (int j = 0; j < NUM_COL; j++)
		{
			if (NULL == m_board[i][j])
			{
				printf(" ");
			}
			else
			{
				switch (m_board[i][j]->GetPlayer())
				{
				case PLAYER1:
					printf("0");
					break;
				case PLAYER2:
					printf("-");
					break;
				default:
					break;
				}
			}
		}
	}
	printf("*\n*************\n");
}


