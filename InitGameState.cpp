#include "InitGameState.h"

CInitGameState::CInitGameState()
{
}

void CInitGameState::HandleStateActivity(IGameContext* a_context)
{
	a_context->InitGameUpdate();
}
