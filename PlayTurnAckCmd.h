#pragma once

#include "ICmd.h"
#include "GameConst.h"

class CPlayTurnAckCmd : public ICmd
{
public:
	CPlayTurnAckCmd();

	void SetCmdReceiver(ICmdReceiver* a_CmdReceiver);

	void SetTurnParams(PLAYER_e a_color, int a_dstColumn);

	virtual void Execute();

private:
	ICmdReceiver* m_CmdReceiver;
	PLAYER_e m_player;
	int m_dstColumn;
};

