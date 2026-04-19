#pragma once
#include "Windows.h"
#include <gl/GL.h>
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
struct TexCoord
{
	GLfloat u;
	GLfloat v;
};
struct Mesh
{
	Vertex* Vertices;
	Color* Colors;
	GLushort* Indices;
	TexCoord* Texcoords;
	int VertexCount, ColorCount, TexCoordCount, IndexCount;
};
struct BasicOBJ
{
	Vertex* Vertices;
	GLushort* Faces;
};
