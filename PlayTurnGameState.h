#pragma once

#include "IGameState.h"

class CPlayTurnGameState : public IGameState
{
public:

	CPlayTurnGameState();

	virtual void HandleStateActivity(IGameContext* a_context);
};

