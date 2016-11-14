#pragma once
#ifndef MATH_CORE_H
#define MATH_CORE_H

#define SIZE_ARRAY 4

class Vector2
{
public:
	Vector2();
	Vector2(float _x, float _y);
	~Vector2();

private:
	float m_x;
	float m_y;
};

class Vector3
{
public:
	Vector3();
	Vector3(float _x, float _y, float _z);
	~Vector3();

private:
	float m_x;
	float m_y;
	float m_z;
};

class Matrix4x4
{
public:
	Matrix4x4();
	~Matrix4x4();

	float Get(int row, int col);
	void Set(int row, int col, float pValue);
	void SetIdentity();

	float* AsArray();

private:
	float m_matrix[SIZE_ARRAY][SIZE_ARRAY];
};

#endif