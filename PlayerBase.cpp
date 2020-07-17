#include "PlayerBase.h"
#include <iostream>

CPlayerBase::CPlayerBase()
{
	m_playCmd = NULL;
}

RETCODE_e CPlayerBase::InitPlayer(PLAYER_e a_player)
{
	m_player = a_player;
	return OK;
}

void CPlayerBase::SetPlayTurnCmd(CPlayTurnAckCmd* a_cmd)
{
	m_playCmd = a_cmd;
}

void CPlayerBase::BuildPlayCmd(int a_dstColumn)
{
	printf("Build play CMD, Color#%d, Col#%d\n", m_player, a_dstColumn);
	
	if (NULL != m_playCmd)
	{
		m_playCmd->SetTurnParams(m_player, a_dstColumn);
		m_playCmd->Execute();
	}
}

RETCODE_e CPlayerBase::CheckPlayValidity(const GAME_STATUS& a_gameState, int a_colToPutDisc)
{
	RETCODE_e rc = NOT_OK;

	if (a_colToPutDisc >= 0 && a_colToPutDisc < NUM_COL)
	{
		for (int i = 0; i < NUM_RAW; i++)
		{
			if ( false == a_gameState.bord.disc[i][a_colToPutDisc].taken )
			{
				rc = OK;
				break;
			}
		}
	}
	
	return rc;
}

