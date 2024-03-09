#pragma once

#include "GameObject.h"
#include"Animation.h"
#include "Animations.h"

#define PLAYER_WIDTH 14
#define ID_MOVE_RIGHT_PLAYER 500
#define ID_MOVE_LEFT_PLAYER 501
#define ID_IDLE_PLAYER 502
#define ID_MOVE_RIGHT_ENEMY 600
#define ID_MOVE_LEFT_ENEMY 601

class Enemy :public GameObject
{
protected:
	float vx;
public:
	Enemy(float x, float y, float vx);
	void Update(DWORD dt);
	void Render();
};

class Player : public GameObject
{
protected:
	float vx;
public:
	Player(float x, float y, float vx);
	void Setvx(float vx)
	{
		this->vx = vx;
	}
	float Getvx()
	{
		return this->vx;
	}
	void Update(DWORD dt);
	void Render();
};