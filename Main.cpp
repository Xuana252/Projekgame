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
#include"Enemy.h"

#include"GameKeyEventHandler.h"

#define WINDOW_CLASS_NAME L"SampleWindow"
#define WINDOW_ICON_PATH L"textures//Contra_Icon.ico"
#define WINDOW_TITLE L"Bai 1"

#define BACKGROUND_COLOR D3DXCOLOR(200.0f/255, 200.0f/255, 255.0f/255, 0.0f)
#define WINDOW_WIDTH 320
#define WINDOW_HEIGTH 275

#define ID_TEX_MARIO 0
#define ID_TEX_MAP 1
#define ID_TEX_ENEMY 2

#define TEXTURE_PATH_MARIO  L"textures//bill_animation.png"
#define TEXTURE_PATH_MAP L"textures//contramap.png"
#define TEXTURE_PATH_ENEMY L"textures//Soldier.png"
Camera* camera = Camera::GetInstace();

Player* player;
#define PLAYER_START_X 50.0f
#define PLAYER_START_Y 140.0f
#define PLEYER_START_VX 0.1f

Enemy* enemy;
#define ENEMY_START_X 50.0f
#define ENEMY_START_Y 140.0f
#define ENEMY_START_VX -0.1f

GameKeyEventHandler* keyHandler;

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
	textures->Add(ID_TEX_ENEMY, TEXTURE_PATH_ENEMY);

	Sprites* sprites = Sprites::GetInstance();
	
	LPTEXTURE texMario = textures->Get(ID_TEX_MARIO);
	LPTEXTURE texMap = textures->Get(ID_TEX_MAP);
	LPTEXTURE texEnemy = textures->Get(ID_TEX_ENEMY);

	sprites->Add(00000, 0, 0, 3328, 240, texMap);
	
	//player idle right
	sprites->Add(9999,0, 32, 24, 67, texMario);
	sprites->Add(10000,25, 32, 49, 67, texMario);
	//player idle left
	sprites->Add(9997, 24, 32, 0, 67, texMario);
	sprites->Add(9998, 49, 32, 25, 67, texMario);

	//player move right
	sprites->Add(10001, 0, 69, 22,105 , texMario);
	sprites->Add(10002, 23, 69, 42, 105, texMario);
	sprites->Add(10003, 43, 69, 62, 105, texMario);
	sprites->Add(10004, 63, 69, 84, 105,texMario);

	//player move left
	sprites->Add(10011, 22, 69, 0, 105,  texMario);
	sprites->Add(10012, 42, 69, 23, 105,  texMario);
	sprites->Add(10013, 62, 69, 43, 105,  texMario);
	sprites->Add(10014, 85, 69, 63, 105,  texMario);

	//player crouch right
	sprites->Add(10018, 82, 32, 116, 65, texMario);
	//player crouch left
	sprites->Add(10019, 116, 32, 82, 65, texMario);

	//player jump right
	sprites->Add(10020, 118, 44, 134, 65, texMario);
	sprites->Add(10021, 135, 44, 154, 65, texMario);
	sprites->Add(10022, 156, 44, 172, 65, texMario);
	sprites->Add(10023, 174, 44, 193, 65, texMario);
	//player jump left
	sprites->Add(10024, 134, 44, 118, 65, texMario);
	sprites->Add(10025, 154, 44, 135, 65, texMario);
	sprites->Add(10026, 172, 44, 156, 65, texMario);
	sprites->Add(10027, 193, 44, 174, 65, texMario);

	//enemy move right
	sprites->Add(20021, 102, 0, 120, 32, texEnemy);
	sprites->Add(20022, 121, 0 ,138, 32, texEnemy);
	sprites->Add(20023, 139, 0, 156, 32, texEnemy);
	sprites->Add(20024, 157, 0, 174, 32, texEnemy);
	sprites->Add(20025, 175, 0, 192, 32, texEnemy);
	sprites->Add(20026, 193, 0, 210, 32, texEnemy);
	sprites->Add(20027, 211, 0, 228, 32, texEnemy);

	//enemy move left
	sprites->Add(20031, 120, 0, 102, 32, texEnemy);
	sprites->Add(20032, 138, 0, 121, 32, texEnemy);
	sprites->Add(20033, 156, 0, 139, 32, texEnemy);
	sprites->Add(20034, 174, 0, 157, 32, texEnemy);
	sprites->Add(20035, 192, 0, 175, 32, texEnemy);
	sprites->Add(20036, 210, 0, 193, 32, texEnemy);
	sprites->Add(20037, 228, 0, 211, 32, texEnemy);

	Animations* animations = Animations::GetInstance();
	LPANIMATION ani;

	ani = new Animation(250);
	ani->Add(9997);
	ani->Add(9998);
	animations->Add(ID_IDLE_LEFT_PLAYER, ani);

	ani = new Animation(250);
	ani->Add(9999);
	ani->Add(10000);
	animations->Add(ID_IDLE_RIGHT_PLAYER, ani);

	ani = new Animation(150);
	ani->Add(10001);
	ani->Add(10002);
	ani->Add(10003);
	ani->Add(10004);
	animations->Add(ID_MOVE_RIGHT_PLAYER, ani);


	ani = new Animation(100);
	ani->Add(10011);
	ani->Add(10012);
	ani->Add(10013);
	ani->Add(10014);
	animations->Add(ID_MOVE_LEFT_PLAYER, ani);

	ani = new Animation(100);
	ani->Add(10018);
	animations->Add(ID_CROUCH_RIGHT_PLAYER, ani);

	ani = new Animation(100);
	ani->Add(10019);
	animations->Add(ID_CROUCH_LEFT_PLAYER, ani);

	ani = new Animation(80);
	ani->Add(10020);
	ani->Add(10021);
	ani->Add(10022);
	ani->Add(10023);
	animations->Add(ID_JUMP_RIGHT_PLAYER, ani);

	ani = new Animation(80);
	ani->Add(10024);
	ani->Add(10025);
	ani->Add(10026);
	ani->Add(10027);
	animations->Add(ID_JUMP_LEFT_PLAYER, ani);

	ani = new Animation(100);
	ani->Add(20021);
	ani->Add(20022);
	ani->Add(20023);
	ani->Add(20024);
	ani->Add(20025);
	ani->Add(20026);
	ani->Add(20027);
	animations->Add(ID_MOVE_RIGHT_ENEMY, ani);

	ani = new Animation(100);
	ani->Add(20031);
	ani->Add(20032);
	ani->Add(20033);
	ani->Add(20034);
	ani->Add(20035);
	ani->Add(20036);
	ani->Add(20037);
	animations->Add(ID_MOVE_LEFT_ENEMY, ani);


	camera->SetCamera(0, 240, WINDOW_WIDTH, WINDOW_HEIGTH);
	camera->SetMap(sprites->Get(00000));
	player = new Player(PLAYER_START_X, PLAYER_START_Y, PLEYER_START_VX);
	enemy = new Enemy(ENEMY_START_X, ENEMY_START_Y, ENEMY_START_VX);

}
void Update(DWORD dt)
{
	
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
	wc.hIcon = (HICON)LoadImage(hInstance, WINDOW_ICON_PATH, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
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
			Game::GetInstance()->ProcessKeyboard();
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
	game->Init(hWnd,hInstance);
	
	keyHandler = new GameKeyEventHandler();

	game->InitKeyboard(keyHandler);

	LoadResource();

	SetWindowPos(hWnd, 0, 0, 0, WINDOW_WIDTH * 2, WINDOW_HEIGTH * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	Run();
	return 0;
}