#pragma once

#include<Windows.h>
#include<D3D10.h>
#include<D3DX10.h>

#include"Texture.h"
#define MAX_FPS 100	

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

public:
	void Init(HWND hWnd);

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