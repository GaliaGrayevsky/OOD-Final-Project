#include "PlayTurnAckCmd.h"

CPlayTurnAckCmd::CPlayTurnAckCmd()
{
}

void CPlayTurnAckCmd::SetCmdReceiver(ICmdReceiver* a_CmdReceiver)
{
	m_CmdReceiver = a_CmdReceiver;
}

void CPlayTurnAckCmd::SetTurnParams(PLAYER_e a_player, int a_dstColumn)
{
	m_player = a_player;
	m_dstColumn = a_dstColumn;
}

void CPlayTurnAckCmd::Execute()
{
	//m_CmdReceiver->ExecuteTurn(m_player, m_dstColumn);
}
