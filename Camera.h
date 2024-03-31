#pragma once
#include<Windows.h>
#include"Sprite.h"
#include"Player.h"
#define WORLD_WIDTH 3328
#define WORLD_HEIGHT 240
class Camera
{
	static Camera* __instance;
	LPSPRITE map;
	float x;
	float y;
	float width;
	float height;
public:
	void SetCamera(float x, float y, float Width, float Height)
	{
		this->x = x;
		this->y = y;
		this->width = Width;
		this->height = Height;
	}
	void SetMap(LPSPRITE tex);
	float ConvertWorldX(float x);
	float ConvertWorldY(float y);
	float getx() { return x; }
	float gety() { return y; }
	void Update(DWORD dt,Player* player);
	void Render();
	static Camera* GetInstace();
};