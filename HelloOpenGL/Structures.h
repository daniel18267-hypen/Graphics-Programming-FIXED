#pragma once
#include "Windows.h"
#include <gl/GL.h>
struct Vector3
{
	float x;
	float y;
	float z;
};
struct Vector4
{
	float x;
	float y;
	float z;
	float w;
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
	Vector3* Normals;
	GLushort* Indices;
	TexCoord* Texcoords;
	int VertexCount, NormalCount, TexCoordCount, IndexCount;
};
struct Lighting
{
	Vector4 ambient;
	Vector4 diffuse;
	Vector4 specular;
};
struct Material
{
	Vector4 ambient;
	Vector4 diffuse;
	Vector4 specular;
	GLfloat shininess;
};
