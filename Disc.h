#pragma once

#include "GameConst.h"


class CDisc
{
public:
	CDisc();

	void ResetDisc();
	void SetDiscParams(PLAYER_e a_diskColor);

	PLAYER_e GetPlayer();

private:
	PLAYER_e m_discPlayer;
};

