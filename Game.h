#pragma once

#include<Windows.h>
#include<D3D10.h>
#include<D3DX10.h>
#include<dinput.h>

#include"Texture.h"
#include"KeyEventHandler.h"
#define DIRECTINPUT_VERSION 0x0800
#define MAX_FPS 60
#define KEYBOARD_BUFFER_SIZE 1024
#define KEYBOARD_STATE_SIZE 256

class Game
{
	static Game* __instance;
	HWND hWnd;

	int backBufferWidth = 0;
	int backBufferHeight = 0;

	ID3D10Device* pD3DDevice = NULL;
	IDXGISwapChain* pSwapChain = NULL;
	ID3D10RenderTargetView* pRenderTargetView = NULL;
	ID3D10BlendState* pBlendStateAlpha = NULL;

	ID3DX10Sprite* spriteObject = NULL;

	LPDIRECTINPUT8	di;
	LPDIRECTINPUTDEVICE8 didv;

	BYTE  keyStates[KEYBOARD_STATE_SIZE];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data

	LPKEYEVENTHANDLER keyHandler;

	HINSTANCE hInstance;

public:
	void Init(HWND hWnd,HINSTANCE hInstance);

	void Draw(float x, float y, LPTEXTURE tex, RECT* rect = NULL);

	void Draw(float x, float y, LPTEXTURE tex, int l, int t, int r, int b)
	{
		RECT rect;
		rect.left = l;
		rect.top = t;
		rect.right = r;
		rect.bottom = b;
		this->Draw(x, y, tex, &rect);
	}

	LPTEXTURE LoadTexture(LPCWSTR texturePath);

	void InitKeyboard(LPKEYEVENTHANDLER handler);
	int IsKeyDown(int KeyCode);
	void ProcessKeyboard();

	ID3D10Device* GetDirect3DDevice() { return this->pD3DDevice; }
	IDXGISwapChain* GetSwapChain() { return this->pSwapChain; }
	ID3D10RenderTargetView* GetRenderTargetView() { return this->pRenderTargetView; }
	ID3DX10Sprite* GetSpriteHandler() { return this->spriteObject; }
	ID3D10BlendState* GetAlphaBlending() { return pBlendStateAlpha; };

	int GetBackBufferWidth() { return backBufferWidth; }
	int GetBackBufferHeight() { return backBufferHeight; }

	static Game* GetInstance();

	~Game();
};