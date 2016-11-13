#include "SpriteBatch.h"
#include "OGL.h"

SpriteBatch::SpriteBatch()
{
	m_vertexBufferID = 0;
	m_texBufferID = 0;
	m_indexBufferID = 0;
	m_vertexArrayID = 0;
}

SpriteBatch::~SpriteBatch()
{
	if (m_vertexBufferID)
	{
		glDeleteBuffers(m_vertexBufferID);
	}
	if (m_texBufferID)
	{
		glDeleteBuffers(m_texBufferID);
	}
	if (m_indexBufferID)
	{
		glDeleteBuffers(m_indexBufferID);
	}
	if (m_vertexArrayID)
	{
		glBindVertexArray(0);
		glDeleteVertexArrays(1, &m_vertexArrayID);
	}
}

void SpriteBatch::Initialize()
{
	glGenVertexArrays(1, &m_vertexArrayID);
	glGenBuffers(1, &m_vertexBufferID);
	glGenBuffers(1, &m_texBufferID);
	glGenBuffers(1, &m_indexBufferID);
}

void SpriteBatch::Draw(RecTangle &pRect)
{
	Vector3 verts[4];
	Vector2 uv[4];
	U32 indices[6];

	m_indicesCount = 6;

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 1;
	indices[4] = 2;
	indices[5] = 3;

	float left = -(pRect.GetRight() / 2.0f);
	float right = left + pRect.GetRight();
	float top = -(pRect.GetBottom() / 2.0f);
	float bottom = top + pRect.GetBottom();

	verts[0] = Vector3(left, top, 0.0f);
	verts[1] = Vector3(right, top, 0.0f);
	verts[2] = Vector3(left, bottom, 0.0f);
	verts[3] = Vector3(right, bottom, 0.0f);

}