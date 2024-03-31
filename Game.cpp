#include"Game.h"
#include"debug.h"

Game* Game::__instance = NULL;


void Game::Init(HWND hWnd,HINSTANCE hInstance)
{
	this->hWnd = hWnd;
	this->hInstance = hInstance;

	RECT r;
	GetClientRect(hWnd, &r);

	backBufferWidth = r.right + 1;
	backBufferHeight = r.bottom + 1;

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	//cau hinh swapchain
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = backBufferWidth;
	swapChainDesc.BufferDesc.Height = backBufferHeight;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = TRUE;

	//tao d3d device va swapchain
	HRESULT hr =D3D10CreateDeviceAndSwapChain(
		NULL,
		D3D10_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		D3D10_SDK_VERSION,
		&swapChainDesc,
		&pSwapChain,
		&pD3DDevice);

	if (hr != S_OK)
	{
		DebugOut((wchar_t*)L"[ERROR] D3D10CreateDeviceAndSwapChain has failed %s %d", _W(__FILE__), __LINE__);
		return;
	}

	//lay backbuffer tu swapchain
	ID3D10Texture2D* pBackBuffer;
	hr = pSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*)&pBackBuffer);

	if (hr != S_OK)
	{
		DebugOut((wchar_t*)L"[ERROR] pSwapChain->GetBuffer has failed %s %d", _W(__FILE__), __LINE__);
		return;
	}
	//tao render target view
	hr = pD3DDevice->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView);

	//giai phong backbuffer
	pBackBuffer->Release();

	if (hr != S_OK)
	{
		DebugOut((wchar_t*)L"[ERROR] CreateRenderTargetView has failed %s %d", _W(__FILE__), __LINE__);
		return;
	}

	pD3DDevice->OMSetRenderTargets(1, &pRenderTargetView, NULL);

	//tao va cau hinh viewport 
	D3D10_VIEWPORT viewPort;
	viewPort.Width = backBufferWidth;
	viewPort.Height = backBufferHeight;
	viewPort.MaxDepth = 1.0f;
	viewPort.MinDepth = 0.0f;
	viewPort.TopLeftX = 0;
	viewPort.TopLeftY = 0;
	pD3DDevice->RSSetViewports(1, &viewPort);

	//tao sprite object de xu ly sprite
	hr = D3DX10CreateSprite(pD3DDevice, 0, &spriteObject);

	if (hr != S_OK)
	{
		DebugOut((wchar_t*)L"[ERROR] D3DX10CreateSprite has failed %s %d", _W(__FILE__), __LINE__);
		return;
	}

	D3DXMATRIX matProjection;

	//su dung gia tri cua viewPort de tao ma tran projection
	D3DXMatrixOrthoOffCenterLH(
		&matProjection,
		(float)viewPort.TopLeftX,
		(float)viewPort.Width,
		(float)viewPort.TopLeftY,
		(float)viewPort.Height,
		0.1f,
		10);
	hr= spriteObject->SetProjectionTransform(&matProjection);

	//
	D3D10_BLEND_DESC StateDesc;
	ZeroMemory(&StateDesc, sizeof(D3D10_BLEND_DESC));
	StateDesc.AlphaToCoverageEnable = FALSE;
	StateDesc.BlendEnable[0] = TRUE;
	StateDesc.SrcBlend = D3D10_BLEND_SRC_ALPHA;
	StateDesc.DestBlend = D3D10_BLEND_INV_SRC_ALPHA;
	StateDesc.BlendOp = D3D10_BLEND_OP_ADD;
	StateDesc.SrcBlendAlpha = D3D10_BLEND_ZERO;
	StateDesc.DestBlendAlpha = D3D10_BLEND_ZERO;
	StateDesc.BlendOpAlpha = D3D10_BLEND_OP_ADD;
	StateDesc.RenderTargetWriteMask[0] = D3D10_COLOR_WRITE_ENABLE_ALL;
	pD3DDevice->CreateBlendState(&StateDesc, &this->pBlendStateAlpha);

	DebugOut((wchar_t*)L"[INFO] InitDirectX has been successful\n");

	return;
}

void Game::Draw(float x, float y, LPTEXTURE tex, RECT* rect)
{
	if (tex == NULL) 
		return;
	int spriteWidth = 0;
	int spriteHeight = 0;

	D3DX10_SPRITE sprite;

	// Set the sprite’s shader resource view
	sprite.pTexture = tex->getShaderResourceView();


	// top-left location in U,V coords
	if (rect == NULL)
	{
		// top-left location in U,V coords
		sprite.TexCoord.x = 0;
		sprite.TexCoord.y = 0;

		// Determine the texture size in U,V coords
		sprite.TexSize.x = 1.0f;
		sprite.TexSize.y = 1.0f;

		spriteWidth = tex->getWidth();
		spriteHeight = tex->getHeight();
	}
	else
	{
		sprite.TexCoord.x = rect->left / (float)tex->getWidth();
		sprite.TexCoord.y = rect->top / (float)tex->getHeight();

		spriteWidth = (rect->right - rect->left + 1);
		spriteHeight = (rect->bottom - rect->top + 1);

		sprite.TexSize.x = spriteWidth / (float)tex->getWidth();
		sprite.TexSize.y = spriteHeight / (float)tex->getHeight();
	}


	// Set the texture index. Single textures will use 0
	sprite.TextureIndex = 0;

	// The color to apply to this sprite, full color applies white.
	sprite.ColorModulate = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//
	// Build the rendering matrix based on sprite location 
	//

	// The translation matrix to be created
	D3DXMATRIX matTranslation;

	// Create the translation matrix
	D3DXMatrixTranslation(&matTranslation, x, (backBufferHeight - y), 0.1f);

	// Scale the sprite to its correct width and height because by default, DirectX draws it with width = height = 1.0f 
	D3DXMATRIX matScaling;
	D3DXMatrixScaling(&matScaling, (FLOAT)spriteWidth, (FLOAT)spriteHeight, 1.0f);

	// Setting the sprite’s position and size
	sprite.matWorld = (matScaling * matTranslation);

	spriteObject->DrawSpritesImmediate(&sprite, 1, 0, 0);
}

LPTEXTURE Game::LoadTexture(LPCWSTR texPATH)
{
	ID3D10Resource* pD3D10Resource = NULL;
	ID3D10Texture2D* tex = NULL;

	HRESULT hr = D3DX10CreateTextureFromFile(
		pD3DDevice,
		texPATH,
		NULL,
		NULL,
		&pD3D10Resource,
		NULL);
	if (FAILED(hr))
	{
		DebugOut((wchar_t*)L"[ERROR] Failed to load texture file: %s with error: %d\n", texPATH, hr);
		return NULL;
	}
	//Bien object ID3D10Resource thanh mot object ID3D10Texture2D
	pD3D10Resource->QueryInterface(__uuidof(ID3D10Texture2D), (LPVOID*)&tex);
	pD3D10Resource->Release();

	if (!tex) {
		DebugOut((wchar_t*)L"[ERROR] Failed to convert from ID3D10Resource to ID3D10Texture2D \n");
		return NULL;
	}

	//lay thong tin texture
	D3D10_TEXTURE2D_DESC desc;
	tex->GetDesc(&desc);

	//tao shader resource view cho texture
	D3D10_SHADER_RESOURCE_VIEW_DESC SRVDesc;

	ZeroMemory(&SRVDesc, sizeof(SRVDesc));

	SRVDesc.Format = desc.Format;
	SRVDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2D;
	SRVDesc.Texture2D.MipLevels = desc.MipLevels;

	ID3D10ShaderResourceView* gSpriteTextureRV = NULL;

	pD3DDevice->CreateShaderResourceView(tex, &SRVDesc, &gSpriteTextureRV);

	DebugOut(L"[INFO] Texture loaded Ok from file: %s \n", texPATH);

	return new Texture(tex, gSpriteTextureRV);
}

int Game::IsKeyDown(int KeyCode)
{
	return (keyStates[KeyCode] & 0x80) > 0;
}

void Game::InitKeyboard(LPKEYEVENTHANDLER handler)
{
	HRESULT hr = DirectInput8Create(this->hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&di, NULL);
	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] DirectInput8Create failed!\n");
		return;
	}

	hr = di->CreateDevice(GUID_SysKeyboard, &didv, NULL);
	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] CreateDevice failed!\n");
		return;
	}

	// Set the data format to "keyboard format" - a predefined data format 
	//
	// A data format specifies which controls on a device we
	// are interested in, and how they should be reported.
	//
	// This tells DirectInput that we will be passing an array
	// of 256 bytes to IDirectInputDevice::GetDeviceState.

	hr = didv->SetDataFormat(&c_dfDIKeyboard);

	hr = didv->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);


	// IMPORTANT STEP TO USE BUFFERED DEVICE DATA!
	//
	// DirectInput uses unbuffered I/O (buffer size = 0) by default.
	// If you want to read buffered data, you need to set a nonzero
	// buffer size.
	//
	// Set the buffer size to DINPUT_BUFFERSIZE (defined above) elements.
	//
	// The buffer size is a DWORD property associated with the device.
	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE;

	hr = didv->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);

	hr = didv->Acquire();
	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] DINPUT8::Acquire failed!\n");
		return;
	}

	this->keyHandler = handler;

	DebugOut(L"[INFO] Keyboard has been initialized successfully\n");
}

void Game::ProcessKeyboard()
{
	HRESULT hr;

	// Collect all key states first
	hr = didv->GetDeviceState(sizeof(keyStates), keyStates);
	if (FAILED(hr))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			HRESULT h = didv->Acquire();
			if (h == DI_OK)
			{
				DebugOut(L"[INFO] Keyboard re-acquired!\n");
			}
			else return;
		}
		else
		{
			//DebugOut(L"[ERROR] DINPUT::GetDeviceState failed. Error: %d\n", hr);
			return;
		}
	}

	keyHandler->KeyState((BYTE*)&keyStates);

	// Collect all buffered events
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	hr = didv->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), keyEvents, &dwElements, 0);
	if (FAILED(hr))
	{
		DebugOut(L"[ERROR] DINPUT::GetDeviceData failed. Error: %d\n", hr);
		return;
	}

	// Scan through all buffered events, check if the key is pressed or released
	for (DWORD i = 0; i < dwElements; i++)
	{
		int KeyCode = keyEvents[i].dwOfs;
		int KeyState = keyEvents[i].dwData;
		if ((KeyState & 0x80) > 0)
			keyHandler->OnKeyDown(KeyCode);
		else
			keyHandler->OnKeyUp(KeyCode);
	}
}

Game::~Game()
{
	pBlendStateAlpha->Release();
	spriteObject->Release();
	pRenderTargetView->Release();
	pSwapChain->Release();
	pD3DDevice->Release();
}
Game* Game::GetInstance()
{
	if (__instance == NULL)
		__instance = new Game();
	return __instance;
}