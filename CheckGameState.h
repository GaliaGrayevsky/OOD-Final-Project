#pragma once

#include "IGameState.h"

class CCheckGameState : public IGameState
{
public:

	CCheckGameState();

	virtual void HandleStateActivity(IGameContext* a_context);
};

