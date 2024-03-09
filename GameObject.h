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
public:
	GameObject(float x, float y) 
	{
		this->x = x;
		this->y = y;
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
};