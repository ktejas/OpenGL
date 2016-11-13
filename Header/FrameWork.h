#pragma once
#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#define WIN32_LEAN_AND_MEAN

#include "OGL.h"

class FrameWork
{
public:
	FrameWork();
	~FrameWork();

	//Initialize our FrameWork
	void Initialize();

	//Run our updates and render for the framework
	void Run();

private:
	//Create OpenGL Window
	bool CreateOpenGLWindow(char * pTitle, int x, int y, int width, int height);
	HINSTANCE m_hInstance;
	char * m_windowTitle;
};

#endif