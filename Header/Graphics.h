#pragma once
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "OGL.h"

static bool FULL_SCREEN = false;
static bool VSYNC_ENABLED = true;

class Graphics
{
public:
	Graphics();
	~Graphics();

	//Initialize OpenGL and the extensions
	bool InitializeOGL(HWND pHWND);

	//Initialize graphics class
	//bool Initialize();

	//Begin Scene
	void BeginScene(float red, float green, float blue, float alpha);

	//End Scene
	void EndScene();

	//Get OpenGL object
	OGL * GetOpenGL();

	//Release the memory
	void Release();

private:
	OGL * m_ogl;
};

#endif