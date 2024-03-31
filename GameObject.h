#pragma once

#include<WIndows.h>
#include<D3D10.h>
#include<vector>

#include"Sprites.h"

using namespace std;

class GameObject
{
protected:
	float x;
	float y;
	float vx;
	float vy;
	int nx;
	int ny;
	int state;
public:
	GameObject(float x, float y) 
	{
		this->x = x;
		this->y = y;
		this->nx = 1;
		this->ny = 1;
		
	}

	void SetPostion(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	float GetX()
	{
		return x;
	}
	float GetY()
	{
		return y;
	}

	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
	virtual void SetState(int state) { this->state = state; }
	int GetState() { return this->state; }
};