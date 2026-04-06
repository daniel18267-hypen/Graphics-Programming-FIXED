#pragma once
struct Vector3
{
	float x;
	float y;
	float z;
};
struct Camera
{
	Vector3 eye;
	Vector3 center;
	Vector3 up;
};
struct Color
{
	GLfloat r;
	GLfloat g;
	GLfloat b;
};
struct Vertex
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
};