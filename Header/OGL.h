#pragma once

#ifndef OGL_H
#define OGL_H

#include "glew.h"
#include "wglew.h"

///////////
//DEFINES//
///////////
#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092

//typedefs that we need to access the OpenGL 4.0 functionality
typedef HGLRC(WINAPI * PFNWGLCREATECONTEXTATTRIBSARBPROC) (HDC hDC, HGLRC hShareContext, const int* attribList);

class OGL
{
public:
	OGL();
	~OGL();

	//Initialize OpenGL Extensions
	bool InitializeExtensions();

	//Initialize OpenGL
	bool InitializeOGL(bool vSync);

	//Begin Scene for OpenGL
	void BeginScene(float red, float green, float blue, float alpha);

	//End the Scene for OpenGL
	void EndScene();

	//Gets name of GPU
	void GetVideoCardInfo(char * pInfo);

	//Get HWND
	HWND GetHWND();

	//Set HWND
	void SetHWND(HWND pHWND);

	//Release OpenGL
	void Release();

private:
	//Load Extensions
	bool LoadExtensions();

	HDC m_deviceContext;
	HGLRC m_renderingContext;
	HWND m_hwnd;
	PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;

	char m_videoCardDescription[128];
};

#endif