#include "ShaderManager.h"

Shader** ShaderManager::m_shaders = NULL;

ShaderManager::ShaderManager()
{

}

ShaderManager::~ShaderManager()
{
	for (int i = 0; i < COUNT; i++)
	{
		delete m_shaders[i];
	}

	delete[] m_shaders;
}

void ShaderManager::Initialize()
{
	m_shaders = new Shader*[COUNT];

	m_shaders[COLOR] = new Shader();
	m_shaders[COLOR]->Initialize("color_vs.glsl", "color_ps.glsl");

	m_shaders[TEXTURE] = new Shader();
}

Shader* ShaderManager::GetShader(ShaderType pType)
{
	return m_shaders[pType];
}