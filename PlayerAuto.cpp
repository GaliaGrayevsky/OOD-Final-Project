#include "PlayerAuto.h"
#include <Windows.h>

CPlayerAuto::CPlayerAuto(PLAYER_LEVEL_e a_playerLevel)
{
	m_levelStartegy = NULL;
	m_level = a_playerLevel;
}

void CPlayerAuto::PlayTurn(const GAME_STATUS& a_gameState)
{
	Sleep(1000);
	int colToPutDisc = 0;
	if (NULL != m_levelStartegy)
	{
		do
		{
			colToPutDisc = m_levelStartegy->playTurn(a_gameState);
		} while (NOT_OK == CheckPlayValidity(a_gameState, colToPutDisc));
	}

	BuildPlayCmd(colToPutDisc);
}
