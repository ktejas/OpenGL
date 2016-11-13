#include "Graphics.h"

Graphics::Graphics()
{
	m_ogl = NULL;
}

Graphics::~Graphics()
{

}

bool Graphics::InitializeOGL(HWND pHWND)
{
	if (!m_ogl)
	{
		m_ogl = new OGL();
	}

	m_ogl->SetHWND(pHWND);

	if (!m_ogl->InitializeExtensions())
	{
		return false;
	}

	return true;
}

void Graphics::BeginScene(float red, float green, float blue, float alpha)
{
	m_ogl->BeginScene(red, green, blue, alpha);
}

void Graphics::EndScene()
{
	m_ogl->EndScene();
}

OGL * Graphics::GetOpenGL()
{
	return m_ogl;
}

void Graphics::Release()
{
	if (m_ogl)
	{
		m_ogl->Release();
		delete m_ogl;
		m_ogl = NULL;
	}
}