#include "FrameWork.h"
#include "Engine.h"
#include "SystemDefs.h"
#include "Timer.h"

LRESULT CALLBACK WndProc(HWND pHwnd, UINT pMessage, WPARAM wParam, LPARAM lParam);

FrameWork::FrameWork()
{
	m_windowTitle = "Teja's Awesome Game";
}

FrameWork::~FrameWork()
{
	if (FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	Engine::GetEngine()->Release();

	UnregisterClass(m_windowTitle, m_hInstance);
	m_hInstance = NULL;
}

void FrameWork::Initialize()
{
	if (!CreateOpenGLWindow(m_windowTitle, WIND_POSX, WIND_POSY, SCREEN_WIDTH, SCREEN_HEIGHT))
	{
		return;
	}

	Engine::GetEngine()->Initialize();
}

void FrameWork::Run()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	//Update Loop
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//Update Timer
			Timer::Update();

			//Run the Engine
			Engine::GetEngine()->Run();
		}
	}
}

bool FrameWork::CreateOpenGLWindow(char * pTitle, int x, int y, int width, int height)
{
	HWND hwnd;

	WNDCLASSEX wc;

	m_hInstance = GetModuleHandle(NULL);

	//Setup the windows class with default settings
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc		= WndProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= m_hInstance;
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm			= wc.hIcon;
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName		= NULL;
	wc.lpszClassName	= pTitle;
	wc.cbSize			= sizeof(WNDCLASSEX);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "RegisterClass failed: Cannot register window class", "Error", MB_OK);
		return false;
	}

	//Create a temporary window for OpenGL extension setup
	hwnd = CreateWindowEx(WS_EX_APPWINDOW, pTitle, pTitle, WS_POPUP, 0, 0, 640, 480, NULL, NULL, m_hInstance, NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "CreateWindowEx failed: Cannot create window", "Error", MB_OK);
		return false;
	}

	//Don't show the window
	ShowWindow(hwnd, SW_HIDE);

	Engine * engine = Engine::GetEngine();
	if (!engine->InitializeGraphics(hwnd))
	{
		MessageBox(hwnd, "Could not initialze the OpenGL Extensions.", "Extreme Error", MB_OK);
		engine->Release();
		PostQuitMessage(0);
		DestroyWindow(hwnd);

		return false;
	}

	//Destroy the temporary window that we created
	DestroyWindow(hwnd);
	hwnd = NULL;

	//Set Window styles for the Window
	int nStyle = WS_OVERLAPPED | WS_SYSMENU | WS_VISIBLE | WS_CAPTION | WS_MINIMIZEBOX;

	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	if (FULL_SCREEN)
	{
		DEVMODE dmScreenSettings;

		//Fullscreen settings
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize			= sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth	= (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight	= (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel	= 32;
		dmScreenSettings.dmFields		= DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		//Change it too fullscreen
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
	}
	else
	{
		screenWidth = width;
		screenHeight = height;
	}

	//Create our window again
	hwnd = CreateWindowEx(WS_EX_APPWINDOW, pTitle, pTitle, nStyle, x, y, screenWidth, screenHeight, NULL, NULL, m_hInstance, NULL);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "CreateWindow failed: Cannot create Window.", "Extreme Error", MB_OK);
		return false;
	}

	OGL * ogl = engine->GetGraphics()->GetOpenGL();
	ogl->SetHWND(hwnd);

	if (!ogl->InitializeOGL(VSYNC_ENABLED))
	{
		MessageBox(hwnd, "Could not initialize OpenGL 4.0.", "Error", MB_OK);
		engine->Release();
		PostQuitMessage(0);
		DestroyWindow(hwnd);

		return false;
	}

	//Show our window
	ShowWindow(hwnd, SW_SHOW);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);

	return true;
}

LRESULT CALLBACK WndProc(HWND pHwnd, UINT pMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (pMessage)
	{
		case WM_KEYDOWN:
		{
			if (wParam == VK_ESCAPE)
			{
				PostQuitMessage(0);
				DestroyWindow(pHwnd);
			}
		}break;

		case WM_KEYUP:
		{
		}break;

		case WM_PAINT:
		{
			hdc = BeginPaint(pHwnd, &ps);
			EndPaint(pHwnd, &ps);
		}break;

		default:
			return DefWindowProc(pHwnd, pMessage, wParam, lParam);
	}

	return 0;
}