#include "Game.h"
#include "Player.h"
#include "Camera.h"

Player::Player(float x, float y, float vx) : GameObject(x, y)
{
	this->vx = vx;
}
Enemy::Enemy(float x, float y, float vx) :GameObject(x, y)
{
	this->vx = vx;
}

void Player::Update(DWORD dt)
{
	x += vx * dt;

	float mapSize = WORLD_WIDTH;
	if (x <= 0 || x >= mapSize - PLAYER_WIDTH)
	{
		if (x <= 0)
			x = 0;
		else if (x >= mapSize - PLAYER_WIDTH)
			x = (float)(mapSize - PLAYER_WIDTH);
	}
}

void Enemy::Update(DWORD dt)
{
	x += vx * dt;
	
	int BackBufferWidth = Game::GetInstance()->GetBackBufferWidth();
	if (x <= 0 || x >= BackBufferWidth - PLAYER_WIDTH)
	{
		vx = -vx;
		if (x <= 0)
			x = 0;
		else if (x >= BackBufferWidth - PLAYER_WIDTH)
			x = (float)(BackBufferWidth - PLAYER_WIDTH);
	}
}
void Player::Render()
{
	LPANIMATION ani;

	if (vx > 0)
		ani = Animations::GetInstance()->Get(ID_MOVE_RIGHT_PLAYER);
	else if(vx<0)
		ani = Animations::GetInstance()->Get(ID_MOVE_LEFT_PLAYER);
	else
		ani = Animations::GetInstance()->Get(ID_IDLE_PLAYER);
	Camera* cam = Camera::GetInstace();
	float Cx = cam->ConvertWorldX(x);
	float Cy = cam->ConvertWorldY(y);
	ani->Render(Cx, Cy);
}

void Enemy::Render()
{
	LPANIMATION ani;

	if (vx > 0)
		ani = Animations::GetInstance()->Get(ID_MOVE_RIGHT_ENEMY);
	else
		ani = Animations::GetInstance()->Get(ID_MOVE_LEFT_ENEMY);
	Camera* cam = Camera::GetInstace();
	float Cx = cam->ConvertWorldX(x);
	float Cy = cam->ConvertWorldY(y);
	ani->Render(Cx, Cy);
}
