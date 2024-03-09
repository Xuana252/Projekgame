#include <windows.h>

#include <D3D10.h>
#include <D3DX10.h>

#include"debug.h"
#include"Game.h"
#include"Textures.h"
#include"Sprite.h"
#include"Sprites.h"
#include"Animation.h"
#include"Animations.h"
#include"Camera.h"

#include"Player.h"


#define WINDOW_CLASS_NAME L"SampleWindow"
#define WINDOW_TITLE L"Bai 1"

#define BACKGROUND_COLOR D3DXCOLOR(200.0f/255, 200.0f/255, 255.0f/255, 0.0f)
#define WINDOW_WIDTH 320
#define WINDOW_HEIGTH 275

#define ID_TEX_MARIO 0
#define ID_TEX_MAP 1

#define TEXTURE_PATH_MARIO  L"D://mario.png"
#define TEXTURE_PATH_MAP L"D://map.png"

Camera* camera = Camera::GetInstace();

Player* player;
#define PLAYER_START_X 30.0f
#define PLAYER_START_Y 45.0f
#define PLEYER_START_VX 0.1f

Enemy* enemy;
#define ENEMY_START_X 0.0f
#define ENEMY_START_Y 45.0f
#define ENEMY_START_VX 0.1f



LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

void LoadResource()
{
	
	Textures* textures = Textures::GetInstance();

	textures->Add(ID_TEX_MARIO,TEXTURE_PATH_MARIO);
	textures->Add(ID_TEX_MAP, TEXTURE_PATH_MAP);
	Sprites* sprites = Sprites::GetInstance();
	
	LPTEXTURE texMario = textures->Get(ID_TEX_MARIO);
	LPTEXTURE texMap = textures->Get(ID_TEX_MAP);

	sprites->Add(00000, 0, 0, 3584, 240, texMap);
	
	//player standstill
	sprites->Add(10000, 213, 154, 230, 181, texMario);
	//player move right
	sprites->Add(10001, 246, 154, 259, 181, texMario);
	sprites->Add(10002, 275, 154, 290, 181, texMario);
	sprites->Add(10003, 304, 154, 321, 181, texMario);
	//player move left
	sprites->Add(10011, 186, 154, 200, 181, texMario);
	sprites->Add(10012, 155, 154, 171, 181, texMario);
	sprites->Add(10013, 125, 154, 141, 181, texMario);
	
	//enemy move right
	sprites->Add(10021, 246, 390, 259, 420, texMario);
	sprites->Add(10022, 275, 390, 290, 420, texMario);
	sprites->Add(10023, 304, 390, 321, 420, texMario);
	//enemy move left
	sprites->Add(10031, 186, 390, 200, 420, texMario);
	sprites->Add(10032, 155, 390, 171, 420, texMario);
	sprites->Add(10033, 125, 390, 141, 420, texMario);

	Animations* animations = Animations::GetInstance();
	LPANIMATION ani;

	ani = new Animation(100);
	ani->Add(10000);
	animations->Add(ID_IDLE_PLAYER, ani);

	ani = new Animation(100);
	ani->Add(10001);
	ani->Add(10002);
	ani->Add(10003);
	animations->Add(ID_MOVE_RIGHT_PLAYER, ani);

	ani = new Animation(100);
	ani->Add(10011);
	ani->Add(10012);
	ani->Add(10013);
	animations->Add(ID_MOVE_LEFT_PLAYER, ani);

	ani = new Animation(100);
	ani->Add(10021);
	ani->Add(10022);
	ani->Add(10023);
	animations->Add(ID_MOVE_RIGHT_ENEMY, ani);

	ani = new Animation(100);
	ani->Add(10031);
	ani->Add(10032);
	ani->Add(10033);
	animations->Add(ID_MOVE_LEFT_ENEMY, ani);
	camera->SetCamera(0, 240, WINDOW_WIDTH, WINDOW_HEIGTH);
	camera->SetMap(sprites->Get(00000));
	player = new Player(PLAYER_START_X, PLAYER_START_Y, PLEYER_START_VX);
	enemy = new Enemy(ENEMY_START_X, ENEMY_START_Y, ENEMY_START_VX);

}
void ProcessInput()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		player->Setvx(-0.1f);
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		player->Setvx(0.1f);
	else
		player->Setvx(0.0f);

	
}
void Update(DWORD dt)
{
	ProcessInput();
	player->Update(dt);
	camera->Update(dt,player);
	enemy->Update(dt);
	
}

void Render()
{
	Game* g = Game::GetInstance();
	ID3D10Device* pDevice = g->GetDirect3DDevice();
	IDXGISwapChain* pSwapChain = g->GetSwapChain();
	ID3D10RenderTargetView* pRenderTargetView = g->GetRenderTargetView();

	ID3DX10Sprite* spriteObject = g->GetSpriteHandler();
	if (pDevice != NULL)
	{
		//don dep buffer target
		pDevice->ClearRenderTargetView(pRenderTargetView, BACKGROUND_COLOR);
		//ve sprite
		spriteObject->Begin(D3DX10_SPRITE_SORT_TEXTURE);

		FLOAT NewBlendFactor[4] = { 0,0,0,0 };
		pDevice->OMSetBlendState(g->GetAlphaBlending(), NewBlendFactor, 0xffffffff);
		
		camera->Render();
		player->Render();
		enemy->Render();

		spriteObject->End();

		
		pSwapChain->Present(0, 0);
	}

}
HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);
	if (!hWnd)
	{
		DWORD ErrCode = GetLastError();
		DebugOut(L"[ERROR] CreateWindow failed! ErrCode: %d\nAt: %s %d \n", ErrCode, _W(__FILE__), __LINE__);
		return 0;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	SetDebugWindow(hWnd);

	return hWnd;
}
int Run()
{
	MSG msg;
	int done = 0;
	ULONGLONG frameStart = GetTickCount64();
	ULONGLONG tickPerFrame = 1000 / MAX_FPS;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		ULONGLONG now = GetTickCount64();

		ULONGLONG dt = now - frameStart;
		if (dt >= tickPerFrame)
		{
			frameStart = now;
			Update((DWORD)dt);
			Render();
		}
	}
	return 1;
}
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, WINDOW_WIDTH,WINDOW_HEIGTH);

	Game* game = Game::GetInstance();
	game->Init(hWnd);

	LoadResource();

	SetWindowPos(hWnd, 0, 0, 0, WINDOW_WIDTH * 2, WINDOW_HEIGTH * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	Run();
	return 0;
}