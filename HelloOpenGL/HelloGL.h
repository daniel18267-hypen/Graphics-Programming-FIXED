#pragma once
#include "GLUTCallbacks.h" // includes GLUTCallbacks header class
#include <Windows.h> // open gl on windows
#include <gl/GL.h> // Open GL
#include <gl/GLU.h> // OPENGL Utilities
#include "GL/freeglut.h" // freeglut library
#include "GLUTCallbacks.h"
#include "Structures.h"
#include "Cube.h"
#include "objectloader.h"
#include "meshloader.h"
#define RefreshRate 16


class HelloGL
{
public:
	//constructor definition

		HelloGL(int argc, char* argv[]);
	// Destructor
		~HelloGL(void);
		void Display();
		void Update();
		void Keyboard(unsigned char key, int x, int y);
		void InitObjects();
		void InitGL(int argc, char* argv[]);
private:
	float rotation;
	Camera* camera;
	Cube* cube[1000];
	objectloader* object[1000];
};

