#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"
#include <iostream>
#include <string>
#include <fstream>
#include "SceneObject.h"

class Cube : public SceneObject
{
private:
	Vector3 _position;
	GLfloat _rotation;
	Material* _material;
	GLfloat rotationx;
	GLfloat rotationy;
	GLfloat rotationz;
public:
	
	Cube(Mesh* mesh,Texture2D* texture,float x,float y,float z);
	~Cube();
	void Draw();
	void Update();
	void InitMaterials();
	void Rotate(GLfloat rotx, GLfloat roty, GLfloat rotz);
};

