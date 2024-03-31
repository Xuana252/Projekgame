#pragma once
#pragma once

#include "KeyEventHandler.h"

class GameKeyEventHandler : public KeyEventHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};