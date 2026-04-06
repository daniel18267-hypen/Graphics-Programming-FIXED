#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"
#include <iostream>
#include <string>
#include <fstream>

class Cube
{
private:
	static Vertex* indexedvertices;
	static Color* indexedcolors;
	static GLushort* indices;
	static int numvertices, numcolors, numindices;
	GLfloat _rotation;
	Vector3 _position;
public:
	
	Cube(float x,float y,float z);
	~Cube();
	static bool Load(char* path);
	void Draw();
	void Update();
};

