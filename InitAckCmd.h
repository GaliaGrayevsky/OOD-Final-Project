#pragma once

#include "ICmd.h"
#include "ICmdReceiver.h"

class CInitAckCmd : public ICmd
{
public:
	CInitAckCmd();

	virtual void SetCmdReceiver(ICmdReceiver* a_CmdReceiver);
	virtual void Execute();

	void SetNumPlayers(int a_numManPlayers);
	void SetGameLevel(PLAYER_LEVEL_e a_gameLevel);

private:
	ICmdReceiver* m_CmdReceiver;
	int m_numManPlayers;
	PLAYER_LEVEL_e m_gameLevel;
};



