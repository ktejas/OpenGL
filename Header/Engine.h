#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include "Graphics.h"

class Engine
{
public:
	~Engine();

	//Initialize the graphics
	bool InitializeGraphics(HWND pHWND);

	//Initialize the Engine
	void Initialize();

	//Update and Render for the Engine
	void Run();

	//Getter for Graphics
	Graphics * GetGraphics();

	//Release Memory
	void Release();

	//Return the singleton for the Engine
	static Engine * GetEngine();

private:
	Engine();

	static Engine * m_engine;
	Graphics * m_graphics;

	SpriteBatch* m_sb;
};

#endif