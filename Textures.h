#pragma once

#include<unordered_map>
#include<D3DX10.h>

#include"Texture.h"

using namespace std;

class Textures
{
	static Textures* __instance;

	unordered_map<int, LPTEXTURE> textures;
public:
	Textures();
	void Add(int id, LPCWSTR filePath);
	LPTEXTURE Get(unsigned int i);

	static Textures* GetInstance();
};