#include "GameKeyEventHandler.h"

#include "Game.h"
#include "debug.h"
#include "Player.h"

extern Player* player;

void GameKeyEventHandler::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_DOWN:
		player->SetState(PLAYER_STATE_CROUCH);
		break;
	case DIK_A:
		player->SetState(PLAYER_STATE_JUMP);
		break;
	}
	
		
	
}

void GameKeyEventHandler::OnKeyUp(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_DOWN:
		player->SetState(PLAYER_STATE_CROUCH_RELEASE);
		break;
	case DIK_A:
		player->SetState(PLAYER_STATE_JUMP_RELEASE);
		break;
	}
	
}

void GameKeyEventHandler::KeyState(BYTE *states)
{
	Game* g = Game::GetInstance();

	if (g->IsKeyDown(DIK_RIGHT))
	{
		player->SetState(PLAYER_STATE_MOVE_RIGHT);
	}
	else if (g->IsKeyDown(DIK_LEFT))
	{
		player->SetState(PLAYER_STATE_MOVE_LEFT);
	}
	else
	{
		player->SetState(PLAYER_STATE_IDLE);
	}
}

