#pragma once
#include "GLUTCallbacks.h" // includes GLUTCallbacks header class
#include <Windows.h> // open gl on windows
#include <gl/GL.h> // Open GL
#include <gl/GLU.h> // OPENGL Utilities
#include "GL/freeglut.h" // freeglut library
#include "GLUTCallbacks.h"
#include "Structures.h"
#include "BasicObject.h"
#include "meshloader.h"
#include "LinkedList.h"
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
		void Mouse(int x, int y);
		void InitObjects();
		void InitLighting();
		void InitGL(int argc, char* argv[]);
		void DrawUI();
		void DrawString(const char* text,  float rasterposx, float rasterposy);
private:
	float rotation;
	int lastx;
	int lasty;
	int xdiff;
	int ydiff;
	float sensitivity;
	float yawrad;
	float pitchrad;
	bool objectselectmode;
	int index;
	int listlength;
	int yaw;
	float offset;
	int pitch;
	int xpos, ypos, zpos;
	bool firstobject;
	std::string camerapos;
	std::string cameramode;
	std::string currentobjectselected;
	Vector3 objectpos;
	Vector3 front;
	Camera* camera;
	LinkedList* linkedlist;
	SceneObject* sceneobject;
	SceneObject* currentobject;
	Vector4* _lightposition;
	Lighting* _lightdata;
};

