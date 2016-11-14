#pragma once
#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include "Shader.h"

class ShaderManager
{
public:
	ShaderManager();
	~ShaderManager();

	enum ShaderType
	{
		COLOR,
		TEXTURE,
		COUNT
	};

	void Initialize();

	static Shader* GetShader(ShaderType pType);

private:
	static Shader** m_shaders;
};

#endif