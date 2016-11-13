#pragma once
#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

#include "MathCore.h"
#include "SystemDefs.h"
#include "RecTangle.h"

class SpriteBatch
{
public:
	SpriteBatch();
	~SpriteBatch();

	//Initialize SpriteBatch
	void Initialize();

	//Draw a simple 2D plane
	void Draw(RecTangle &pRect);

private:
	U32 m_vertexBufferID;
	U32 m_texBufferID;
	U32 m_indexBufferID;
	U32 m_vertexArrayID;

	int m_indicesCount;
};

#endif