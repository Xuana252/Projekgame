#include "Game.h"
#include "Player.h"
#include "Camera.h"

Player::Player(float x, float y, float vx) : GameObject(x, y)
{
	this->vx = vx;
	this->maxvx = 0.2f;
}


void Player::Update(DWORD dt)
{
	vx += ax * dt;

	if (vx >= maxvx) vx = maxvx;

	vy += dt*-PLAYER_GRAVITY;

	if (y + vy * dt  >= GROUND_Y)
	{
		y += vy * dt ;
	}
	else
	{
		airborne = false;
		y = GROUND_Y;
	}

	if (x+vx*dt*nx >= 0 && x + vx * dt*nx <= WORLD_WIDTH - PLAYER_WIDTH)
	{
		x += nx*vx * dt;
	}
}


void Player::Render()
{
	LPANIMATION ani;
	if (isCrouching)
	{
		if(nx==1)
			ani= Animations::GetInstance()->Get(ID_CROUCH_RIGHT_PLAYER);
		else
			ani = Animations::GetInstance()->Get(ID_CROUCH_LEFT_PLAYER);
	}
	else if(y==GROUND_Y)
	{
		if (this->state == PLAYER_STATE_MOVE_RIGHT)
		{
			ani = Animations::GetInstance()->Get(ID_MOVE_RIGHT_PLAYER);
		}
		else if (this->state == PLAYER_STATE_MOVE_LEFT)
		{
			ani = Animations::GetInstance()->Get(ID_MOVE_LEFT_PLAYER);
		}
		else 
		{
			if(nx==1)
				ani = Animations::GetInstance()->Get(ID_IDLE_RIGHT_PLAYER);
			else
				ani = Animations::GetInstance()->Get(ID_IDLE_LEFT_PLAYER);
		}
			
	}
	else
	{
		if(nx==1)
			ani = Animations::GetInstance()->Get(ID_JUMP_RIGHT_PLAYER);
		else
			ani = Animations::GetInstance()->Get(ID_JUMP_LEFT_PLAYER);

	}
	
	Camera* cam = Camera::GetInstace();
	float Cx = cam->ConvertWorldX(x);
	float Cy = cam->ConvertWorldY(y);
	ani->Render(Cx, Cy);
}

void Player::SetState(int state)
{
	switch (state)
	{
	case PLAYER_STATE_IDLE:
		vx = 0.0f;
		ax = 0.0f;
		break;
	case PLAYER_STATE_MOVE_RIGHT:
		if (isCrouching)break;
		maxvx = PLAYER_MOVE_SPEED;
		ax = PLAYER_ACCEL_SPEED;
		nx = 1;
		break;
	case PLAYER_STATE_MOVE_LEFT:
		if (isCrouching) break;
		maxvx = PLAYER_MOVE_SPEED;
		ax = PLAYER_ACCEL_SPEED;
		nx = -1;
		break;
	case PLAYER_STATE_JUMP:
		if (isCrouching)break;
		if (y == GROUND_Y)
		{
			vy = PLAYER_JUMP_SPEED;
			isCrouching = false;
			airborne = true;
			break;
		}
		
	case PLAYER_STATE_JUMP_RELEASE:
	/*	vy += -PLAYER_JUMP_SPEED/2;*/
		break;
	case PLAYER_STATE_CROUCH:
		if (airborne)break;
		isCrouching = true;
		ax = 0.0f;
		vx = 0.0f;
		vy = 0.0f;
		
		break;
	case PLAYER_STATE_CROUCH_RELEASE:
		if (isCrouching)
		{
			isCrouching = false;
			state = PLAYER_STATE_IDLE;
		}
		break;
	}
	GameObject::SetState(state);
}


