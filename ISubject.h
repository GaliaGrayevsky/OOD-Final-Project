#pragma once

#include "IGameObserver.h"
#include "GameConst.h"

class ISubject
{
public:
	ISubject() {};

	virtual RETCODE_e RegisterToSubject(IGameObserver * a_observer) = 0;
};
