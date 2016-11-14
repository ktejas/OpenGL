#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <fstream>

#include "OGL.h"
#include "MathCore.h"
#include "SystemDefs.h"

class Shader
{
public:
	Shader();
	~Shader();

	//Initialize our Vertex and Pixel Shaders
	bool Initialize(const char* vsFileName, const char* psFileName);

	//Bind the Attributes
	void BindAttributes(int index, const char* pName);

	//Begin Shader
	void BeginShader();

	//End Shader
	void EndShader();

	//Set matrix to Shader
	bool SetShaderMatrixParameter(const char* pName, float* pMatrix);

	//Set float value to Shader
	bool SetShaderFloatParameter(const char* pName, float pValue);

	//Set Int value to Shader
	bool SetShaderIntParameter(const char* pName, int pValue);

	//Set Vector2 to Shader
	bool SetShaderVec2Parameter(const char* pName, Vector2 pValue);

	//Set Vector3 to Shader
	bool SetShaderVec3Parameter(const char* pName, Vector3 pValue);

	//Set Sampler to Shader (Textures)
	bool SetShaderSamplerParameter(const char* pName, int pSlot, int pHandle);

private:
	//Initialize shaders
	bool InitializeShader(const char* vsFileName, const char* psFileName);

	//Load the Shader
	char* LoadShaderSourceFile(const char* pFileName);

	//Debug error Shader message
	void ShaderErrorMessage(U32 pShaderID, const char* pShaderFileName);

	//Linker Error Message
	void LinkerErrorMessage(U32 pProgramID);

	U32 m_vertexShader;
	U32 m_pixelShader; //Same as Fragment Shader
	U32 m_shaderProgram;

};

#endif