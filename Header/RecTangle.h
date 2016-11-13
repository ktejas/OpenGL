#pragma once
#ifndef RECTANGLE_H
#define RECTANGLE_H

class RecTangle
{
public:
	RecTangle();
	RecTangle(float _left, float _top, float _width, float _height);

	~RecTangle();

	float GetLeft();
	float GetRight();
	float GetTop();
	float GetBottom();
	float GetWidth();
	float GetHeight();

private:
	float m_left;
	float m_right;
	float m_top;
	float m_bottom;
	float m_width;
	float m_height;
};

#endif