#include "Shader.h"

#include <iostream>

using namespace std;

Shader::Shader()
{

}

Shader::~Shader()
{
	glDetachShader(m_shaderProgram, m_vertexShader);
	glDetachShader(m_shaderProgram, m_pixelShader);
	glDeleteShader(m_vertexShader);
	glDeleteShader(m_pixelShader);
	glDeleteProgram(m_shaderProgram);
}

bool Shader::Initialize(const char * vsFileName, const char * psFileName)
{
	char vs[128] = "Shaders/";
	strcat_s(vs, vsFileName);

	char ps[128] = "Shaders/";
	strcat_s(ps, psFileName);

	if (!InitializeShader(vs, ps))
	{
		cout << "Shader " << vs << ps << " couldn't be initialized." << endl;

		return false;
	}

	return true;
}

bool Shader::InitializeShader(const char * vsFileName, const char * psFileName)
{
	const char* vertexShaderBuffer;
	const char* pixelShaderBuffer;
	int status;

	//Load Vertex Shader
	vertexShaderBuffer = LoadShaderSourceFile(vsFileName);

	if (!vertexShaderBuffer)
	{
		cout << "Shader Vertex Buffer couldn't be initialized." << endl;

		return false;
	}

	//Load Pixel Shader
	pixelShaderBuffer = LoadShaderSourceFile(psFileName);

	if (!pixelShaderBuffer)
	{
		cout << "Shader Pixel Buffer couldn't be initialized." << endl;

		return false;
	}

	//Create a Vertex and Pixel Shader object
	m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	m_pixelShader = glCreateShader(GL_FRAGMENT_SHADER);

	//Copy the Shader source file into the Vertex and Fragment objects
	glShaderSource(m_vertexShader, 1, &vertexShaderBuffer, NULL);
	glShaderSource(m_pixelShader, 1, &pixelShaderBuffer, NULL);

	//Release the buffers
	delete[] vertexShaderBuffer;
	vertexShaderBuffer = 0;
	delete[] pixelShaderBuffer;
	pixelShaderBuffer = 0;

	//Compile the Shaders
	glCompileShader(m_vertexShader);
	glCompileShader(m_pixelShader);

	//Check if they compile successfully
	glGetShaderiv(m_vertexShader, GL_COMPILE_STATUS, &status);
	if (status != 1)
	{
		ShaderErrorMessage(m_vertexShader, vsFileName);
		return false;
	}
	glGetShaderiv(m_pixelShader, GL_COMPILE_STATUS, &status);
	if (status != 1)
	{
		ShaderErrorMessage(m_pixelShader, psFileName);
		return false;
	}

	//Create a Shader Program Object
	m_shaderProgram = glCreateProgram();

	//Attach Vertex and Pixel Shaders to Program
	glAttachShader(m_shaderProgram, m_vertexShader);
	glAttachShader(m_shaderProgram, m_pixelShader);

	//Link the Program
	glLinkProgram(m_shaderProgram);

	//Check the status
	glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &status);
	if (status != 1)
	{
		LinkerErrorMessage(m_shaderProgram);
		return false;
	}

	return true;
}

char * Shader::LoadShaderSourceFile(const char * pFileName)
{
	ifstream fin;
	long int fileSize = 0;
	char* buffer;

	// Open the shader source file
	fin.open(pFileName);

	// If it could not open the file then exit
	if (fin.fail() == true)
	{
		return 0;
	}

	// Find filesize
	fin.seekg(0, fin.end);
	fileSize = (long)fin.tellg();

	// Place get pointer at the beginning
	fin.seekg(0, fin.beg);

	// Initialize the buffer to read the shader source file into
	// Not sure if I should add 1
	buffer = new char[fileSize];
	if (buffer == nullptr)
	{
		fin.close();
		return 0;
	}

	// Read the shader text file into the buffer as a block
	fin.read(buffer, fileSize);

	// Close the file
	fin.close();

	// Null terminate the buffer
	// Don't know if this is needed
	buffer[fileSize] = '\0';

	return buffer;
}

void Shader::ShaderErrorMessage(U32 pShaderID, const char * pShaderFileName)
{
	int logSize, i;
	char* infoLog;
	ofstream fout;

	// Get the size of the string containing the information log for the failed
	// shader compilation message.
	glGetShaderiv(pShaderID, GL_INFO_LOG_LENGTH, &logSize);

	// Increment the size by one to handle also the null terminator.
	logSize++;

	// Create a char buffer to hold the info log.
	infoLog = new char[logSize];
	if (!infoLog)
	{
		return;
	}

	// Now retrieve the info log.
	glGetShaderInfoLog(pShaderID, logSize, NULL, infoLog);

	// Open a file to write the error message to.
	fout.open("shader-error.txt");

	// Write out the error message.
	for (i = 0; i < logSize; i++)
	{
		fout << infoLog[i];
	}

	// Close the file.
	fout.close();

	cout << "Shader Filename:\n" << pShaderFileName << "\n";
	cout << "Shader Compile Error:\n" << infoLog << "\n";

	delete[] infoLog;
}

void Shader::LinkerErrorMessage(U32 pProgramID)
{
	int logSize, i;
	char* infoLog;
	ofstream fout;


	// Get the size of the string containing the information log for the failed
	// shader compilation message.
	glGetProgramiv(pProgramID, GL_INFO_LOG_LENGTH, &logSize);

	// Increment the size by one to handle also the null terminator.
	logSize++;

	// Create a char buffer to hold the info log.
	infoLog = new char[logSize];
	if (!infoLog)
	{
		return;
	}

	// Now retrieve the info log.
	glGetProgramInfoLog(pProgramID, logSize, NULL, infoLog);

	// Open a file to write the error message to
	fout.open("linker-error.txt");

	// Write out the error message
	for (i = 0; i < logSize; i++)
	{
		fout << infoLog[i];
	}

	// Close the file.
	fout.close();

	cout << "Shader Program:\n" << pProgramID << "\n";
	cout << "Shader Linker Error:\n" << infoLog << "\n";

	delete[] infoLog;
}
