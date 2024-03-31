#pragma once

#include "GameObject.h"
#include"Animation.h"
#include "Animations.h"

#define GROUND_Y 140
#define PLAYER_WIDTH 25

#define PLAYER_MOVE_SPEED 0.1f
#define PLAYER_JUMP_SPEED 0.18f
#define PLAYER_ACCEL_SPEED 0.0002f;

#define PLAYER_GRAVITY 0.0003f;

#define PLAYER_STATE_IDLE 0
#define PLAYER_STATE_MOVE_RIGHT 100
#define PLAYER_STATE_MOVE_LEFT 200

#define PLAYER_STATE_CROUCH 300
#define PLAYER_STATE_CROUCH_RELEASE 301

#define PLAYER_STATE_JUMP 350
#define PLAYER_STATE_JUMP_RELEASE 351

#define ID_CROUCH_RIGHT_PLAYER 400
#define ID_CROUCH_LEFT_PLAYER 401
#define ID_MOVE_RIGHT_PLAYER 500
#define ID_MOVE_LEFT_PLAYER 502
#define ID_IDLE_RIGHT_PLAYER 488
#define ID_IDLE_LEFT_PLAYER 499
#define ID_JUMP_RIGHT_PLAYER 600
#define ID_JUMP_LEFT_PLAYER 601


class Player : public GameObject
{
protected:
	bool isCrouching=false;
	bool airborne = false;
	float ax=0.0f;
	float maxvx=3.0f;
public:
	Player(float x, float y, float vx);
	float Getvx()
	{
		return this->vx*nx;
	}
	void Update(DWORD dt);
	void Render();
	void SetState(int state);
};