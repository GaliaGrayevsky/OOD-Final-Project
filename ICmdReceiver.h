#pragma once

class ICmdReceiver
{
public:

	virtual void InitGameAck(int m_numManPlayers, int a_gameLevel) = 0;
};

