#include "InitAckCmd.h"

CInitAckCmd::CInitAckCmd()
{
	m_numManPlayers = 0;
	m_gameLevel = 0;
}

void CInitAckCmd::SetCmdReceiver(ICmdReceiver* a_CmdReceiver)
{
	m_CmdReceiver = a_CmdReceiver;
}

void CInitAckCmd::Execute()
{
	m_CmdReceiver->InitGameAck(m_numManPlayers, m_gameLevel);
}

void CInitAckCmd::SetNumPlayers(int a_numManPlayers)
{
	m_numManPlayers = a_numManPlayers;
}

void CInitAckCmd::SetGameLevel(PLAYER_LEVEL_e a_gameLevel)
{
	m_gameLevel = a_gameLevel;
}
