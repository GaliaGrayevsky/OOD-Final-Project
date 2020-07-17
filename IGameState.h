#pragma once

#include "IGameContext.h"

class IGameState
{
public:

	virtual void HandleStateActivity(IGameContext* a_context) = 0;
};
