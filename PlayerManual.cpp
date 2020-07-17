#include "PlayerManual.h"
#include <iostream>

CPlayerManual::CPlayerManual()
{
}


void CPlayerManual::PlayTurn(const GAME_STATUS& a_gameState)
{
	int col = 0;
	RETCODE_e LegalMove = NOT_OK;
	do
	{
		printf("Please Choose Column To Put Disc (0..%d):  ", NUM_COL-1);
		scanf_s("%d", &col);
		
		if ( OK == CheckPlayValidity(a_gameState, col))
		{
			LegalMove = OK;
		}
		else
		{
			printf("ILLEGAL COL. Should be (1..%d) in a Valid column\n", NUM_COL);
		}
	} while (LegalMove != OK);
	
	BuildPlayCmd(col);
}

