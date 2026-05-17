#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
class Texture2D
{
private:
	GLuint ID;
	int width, height;
	bool flipped;
	int filesize;
	char* tempheaderdata, * temptexturedata;
	char type, pixeldepth, mode;
public:
	Texture2D();
	~Texture2D();
	int Load(const char* path);
	GLuint GetID() const { return ID; }
	int GetWidth() const { return width;  }
	int GetHeight() const { return height; }
};

