#include "Engine.h"

#include <random>

Engine* Engine::m_engine = NULL;

Engine::Engine()
{
	m_graphics = NULL;
	m_sb = NULL;
}

Engine::~Engine()
{

}

//Initialize the graphics and OpenGL
bool Engine::InitializeGraphics(HWND pHWND)
{
	m_graphics = new Graphics();

	return m_graphics->InitializeOGL(pHWND);
}

//Initialize the Engine
void Engine::Initialize()
{
	m_graphics->Initialize();
}

//Updates and Renders the engine
void Engine::Run()
{
	//Updates the scene
	m_graphics->BeginScene((float)(rand() % 255) / 255, (float)(rand() % 255) / 255, (float)(rand() % 255) / 255, (float)(rand() % 255) / 255);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Render our scene
	//RecTangle rect = RecTangle(0, 0, 64, 64);

	//m_sb->Draw(rect);

	m_graphics->EndScene();
}

//Release the memory
void Engine::Release()
{
	if (m_graphics)
	{
		m_graphics->Release();
		delete m_graphics;
		m_graphics = NULL;
	}

	if (m_engine)
	{
		delete m_engine;
		m_engine = NULL;
	}

	if (m_sb)
	{
		delete m_sb;
	}
}

Graphics * Engine::GetGraphics()
{
	return m_graphics;
}

Engine * Engine::GetEngine()
{
	if (!m_engine)
	{
		m_engine = new Engine();
	}

	return m_engine;
}