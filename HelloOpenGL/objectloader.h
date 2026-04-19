#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"
#include <iostream>
#include <string>
#include <fstream>
#include <assert.h>
#include <vector>
class objectloader
{
private:
	GLfloat _rotation;
	Vector3 _position;
	std::vector<Vertex>* Vertices;
	std::vector<Vertex>* Faces;
	
	char currentcharacter;
	int mode;
public:
	objectloader(float x, float y, float z);
	~objectloader();
	void Update();
	BasicOBJ* LoadBasic(const char* path);
};

