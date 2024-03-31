#pragma once

#include"Texture.h"
#include"Game.h"

class Sprite
{
	int id;

	int left;
	int top;
	int right;
	int bottom;
	int flip = 1;
	LPTEXTURE texture;
	D3DX10_SPRITE sprite;
	D3DXMATRIX matScaling;
public:
	Sprite(int id, int left, int top, int right, int bottom, LPTEXTURE tex);

	void Draw(float x, float y);
};

typedef Sprite* LPSPRITE;