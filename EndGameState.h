#pragma once

#include "IGameState.h"

class CEndGameState : public IGameState
{
public:
	
	CEndGameState();

	virtual void HandleStateActivity(IGameContext* a_context);
};

