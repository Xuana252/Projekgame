#include "Game.h"
#include "Enemy.h"
#include "Camera.h"

Enemy::Enemy(float x, float y, float vx) :GameObject(x, y)
{
	this->vx = vx;
}
void Enemy::Update(DWORD dt)
{
	x += vx * dt;

	int BackBufferWidth = Game::GetInstance()->GetBackBufferWidth();
	if (x <= 0 || x >= WORLD_WIDTH - PLAYER_WIDTH)
	{
		vx = -vx;
		if (x <= 0)
			x = 0;
		else if (x >= WORLD_WIDTH - PLAYER_WIDTH)
			x = (float)(WORLD_WIDTH - PLAYER_WIDTH);
	}
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