#include "Disc.h"

CDisc::CDisc()
{
}

void CDisc::SetDiscParams(PLAYER_e a_discColor)
{
	m_discPlayer = a_discColor;
}

PLAYER_e CDisc::GetPlayer() {
	return m_discPlayer;
}