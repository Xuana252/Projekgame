#include<Windows.h>

#include"Game.h"
#include"Textures.h"

Textures* Textures::__instance = NULL;

Textures::Textures()
{

}

Textures* Textures::GetInstance()
{
	if (__instance == NULL)
		__instance = new Textures();
	return __instance;
}

void Textures::Add(int id, LPCWSTR filePath)
{
	textures[id] = Game::GetInstance()->LoadTexture(filePath);
}

LPTEXTURE Textures::Get(unsigned int i)
{
	return textures[i];
}