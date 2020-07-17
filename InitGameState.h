#pragma once

#include "IGameState.h"

class CInitGameState :  public IGameState
{
public:
	CInitGameState(); 

	virtual void HandleStateActivity(IGameContext* a_context);
};

