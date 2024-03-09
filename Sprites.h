#pragma once

#include<windows.h>
#include<unordered_map>
#include<D3DX10.h>
#include<string>
#include"Texture.h"
#include"Sprite.h"

using namespace std;

class Sprites
{
	static Sprites* __instance;

	unordered_map<int, LPSPRITE> sprites;

public:
	void Add(int id, int left, int top, int right, int bottom, LPTEXTURE tex);
	LPSPRITE Get(int id);
	static Sprites* GetInstance();
};
