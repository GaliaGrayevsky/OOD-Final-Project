#pragma once

#include "ICmdReceiver.h"

class ICmd
{
public:

	virtual void SetCmdReceiver(ICmdReceiver* a_CmdReceiver)=0;
	virtual void Execute() = 0;
};

