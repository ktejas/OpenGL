#include "RecTangle.h"

RecTangle::RecTangle()
{
	m_left = m_right = m_top = m_bottom = m_width = m_height = 0;
}

RecTangle::RecTangle(float _left, float _top, float _width, float _height)
{
	m_left = _left;
	m_right = m_left + _width;
	m_top = _top;
	m_bottom = m_top + _height;

	m_width = _width;
	m_height = _height;
}

float RecTangle::GetLeft()
{
	return m_left;
}

float RecTangle::GetRight()
{
	return m_right;
}

float RecTangle::GetTop()
{
	return m_top;
}

float RecTangle::GetBottom()
{
	return m_bottom;
}

float RecTangle::GetWidth()
{
	return m_width;
}

float RecTangle::GetHeight()
{
	return m_height;
}