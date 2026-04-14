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
	Mesh* _mesh;
	Vector3 _position;
	GLfloat _rotation;
public:
	
	Cube(Mesh* mesh,float x,float y,float z);
	~Cube();
	void Draw();
	void Update();
};

