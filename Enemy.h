#pragma once

#include "GameObject.h"
#include"Animation.h"
#include "Animations.h"

#define ID_MOVE_RIGHT_ENEMY 1600
#define ID_MOVE_LEFT_ENEMY 1601

class Enemy :public GameObject
{
public:
	Enemy(float x, float y, float vx);
	void Update(DWORD dt);
	void Render();
};
