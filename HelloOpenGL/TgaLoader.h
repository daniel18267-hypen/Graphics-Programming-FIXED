#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
class TgaLoader
{
public:
	TgaLoader();
	~TgaLoader();
	int LoadTGA(const char* path);
private:
	GLuint id;
	int width;
	int height;
	int filesize;
	char* tempheaderdata, *temptexturedata;
	char type, pixeldepth, mode;
	bool flipped;
};

