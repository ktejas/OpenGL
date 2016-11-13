#include "OGL.h"

#include <iostream>
using namespace std;

OGL::OGL()
{
	m_deviceContext = 0;
	m_renderingContext = 0;
}

OGL::~OGL()
{

}

//Initialize OpenGL
bool OGL::InitializeOGL(bool vSync)
{
	cout << "Initialized OpenGL" << endl;

	int attributeListInt[19] = { 0 };
	int pixelFormat;
	int result = 0;
	PIXELFORMATDESCRIPTOR pixelFormatDecriptor;
	int attributeList[5];
	char* vendorChar, *rendererChar;

	//Get the device
	m_deviceContext = GetDC(m_hwnd);
	if (!m_deviceContext)
	{
		return false;
	}
	/*
	//Set OpenGL Renderer
	attributeListInt[0] = WGL_SUPPORT_OPENGL_ARB;
	attributeListInt[1] = TRUE;

	//Support for window rendering
	attributeListInt[2] = WGL_DRAW_TO_WINDOW_ARB;
	attributeListInt[3] = TRUE;

	//Support for Hardware Acceleration
	attributeListInt[4] = WGL_ACCELERATION_ARB;
	attributeListInt[5] = WGL_FULL_ACCELERATION_ARB;

	//Support for 24-bit color
	attributeListInt[6] = WGL_COLOR_BITS_ARB;
	attributeListInt[7] = 24;

	//Support for 24-bit depth buffer
	attributeListInt[8] = WGL_DEPTH_BITS_ARB;
	attributeListInt[9] = 24;

	//Support for double buffer
	attributeListInt[10] = WGL_DOUBLE_BUFFER_ARB;
	attributeListInt[11] = TRUE;

	//Support for swapping front and back buffers
	attributeListInt[12] = WGL_SWAP_METHOD_ARB;
	attributeListInt[13] = WGL_SWAP_EXCHANGE_ARB;

	//Support for RGBA pixel type
	attributeListInt[14] = WGL_PIXEL_TYPE_ARB;
	attributeListInt[15] = WGL_TYPE_RGBA_ARB;

	//Support for 8-bit Stencil buffer
	attributeListInt[16] = WGL_STENCIL_BITS_ARB;
	attributeListInt[17] = 8;

	//NULL Terminator
	attributeListInt[18] = 0;
	*/
	//Query for a pixel format that will get the attributes that we want
	pixelFormat = ChoosePixelFormat(m_deviceContext, &pixelFormatDecriptor);
	if (pixelFormat == 0)
	{
		return false;
	}

	//If the video card can handle our desired pixel format
	result = SetPixelFormat(m_deviceContext, pixelFormat, &pixelFormatDecriptor);
	if (result != 1)
	{
		return false;
	}

	//Make a temporary context that will initialize our OpenGL renderer
	HGLRC rempOpenGLContext = wglCreateContext(m_deviceContext); // Creates OpenGL 2.1
	wglMakeCurrent(m_deviceContext, rempOpenGLContext);

	if (glewInit() != GLEW_OK)
	{
		return false;
	}

	//Set the 4.0 version of OpenGL
	attributeList[0] = WGL_CONTEXT_MAJOR_VERSION_ARB;
	attributeList[1] = 4;
	attributeList[2] = WGL_CONTEXT_MINOR_VERSION_ARB;
	attributeList[3] = 0;
	attributeList[4] = 0;

	//Create an OpenGL 4.0 Rendering Context
	m_renderingContext = wglCreateContextAttribsARB(m_deviceContext, 0, attributeList);
	if (m_renderingContext != NULL)
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(rempOpenGLContext);

		//Set the Rendering Context to 4.0
		result = wglMakeCurrent(m_deviceContext, m_renderingContext);
		if (result != 1)
		{
			return false;
		}
	}

	vendorChar = (char *)glGetString(GL_VENDOR);
	rendererChar = (char *)glGetString(GL_RENDERER);

	//Store the info of our graphics card
	strcpy_s(m_videoCardDescription, vendorChar);
	strcat_s(m_videoCardDescription, "-");
	strcat_s(m_videoCardDescription, rendererChar);

	if (vSync)
	{
		result = wglSwapIntervalEXT(1);
	}
	else
	{
		result = wglSwapIntervalEXT(0);
	}

	//Make sure vSync is set correctly
	if (result != 1)
	{
		return false;
	}

	int glVersion[2] = { -1, -1 };
	glGetIntegerv(GL_MAJOR_VERSION, &glVersion[0]);
	glGetIntegerv(GL_MINOR_VERSION, &glVersion[1]);

	cout << "Initializing OpenGL Success." << endl;
	cout << "Using OpenGL: " << glVersion[0] << "." << glVersion[1] << endl;
	cout << "GPU: " << m_videoCardDescription << endl;
	return true;
}

//Initialize OpenGL Extensions
bool OGL::InitializeExtensions()
{
	HDC deviceContext;
	PIXELFORMATDESCRIPTOR pixelFormat;
	int error = 0;
	HGLRC renderContext;
	bool result = false;

	//Get device context for this window;
	deviceContext = GetDC(m_hwnd);
	if (!deviceContext)
	{
		return false;
	}

	//Set temporary default pixel format
	error = SetPixelFormat(deviceContext, 1, &pixelFormat);
	if (error != 1)
	{
		return false;
	}

	//Create temporary Render Context
	renderContext = wglCreateContext(deviceContext);
	if (!renderContext)
	{
		return false;
	}

	//Set temporary render context as the current rendering context
	error = wglMakeCurrent(deviceContext, renderContext);
	if (error != 1)
	{
		return false;
	}

	//Initialize extensions
	result = LoadExtensions();
	if (!result)
	{
		return false;
	}

	//Release
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(renderContext);
	renderContext = NULL;
	ReleaseDC(m_hwnd, deviceContext);
	deviceContext = 0;

	return true;
}

//Load OpenGL Extensions
bool OGL::LoadExtensions()
{
	wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
	if (!wglCreateContextAttribsARB)
	{
		return false;
	}
	return true;
}

//Begin Scene for OpenGL
void OGL::BeginScene(float red, float green, float blue, float alpha)
{
	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//End Scene for OpenGL
void OGL::EndScene()
{
	glFlush();
	SwapBuffers(m_deviceContext);
	glFinish();
}

//Release OpenGL
void OGL::Release()
{
	if (m_renderingContext)
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(m_renderingContext);
		m_renderingContext = 0;
	}

	if (m_deviceContext)
	{
		ReleaseDC(m_hwnd, m_deviceContext);
		m_deviceContext = 0;
	}
}

//Get HWND
HWND OGL::GetHWND()
{
	return m_hwnd;
}

//Set HWND
void OGL::SetHWND(HWND pHWND)
{
	m_hwnd = pHWND;
}