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
		static std::vector<Vertex>* indexedvertices;
		static std::vector<Vertex>* faces;
		static int numvertices, numfaces;
		static char currentcharacter;
		static int mode;
		static int vertexindex;
		static int facesindex;
		static int loopcount;
		static int vertexcount;
		static int facecount;
		GLfloat _rotation;
		Vector3 _position;
	public:
		objectloader(float x, float y, float z);
		~objectloader();
		static bool Load(char* path);
		void Draw();
		void Update();
};

