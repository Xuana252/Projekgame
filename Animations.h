#pragma once

#include "Animation.h"
#include "Sprite.h"

class Animations
{
	static Animations* __instance;

	unordered_map<int, LPANIMATION> animations;
public:
	void Add(int id, LPANIMATION);
	LPANIMATION Get(int id);

	static Animations* GetInstance();
};