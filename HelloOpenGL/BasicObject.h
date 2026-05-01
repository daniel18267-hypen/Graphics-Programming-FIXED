#pragma once
#include "SceneObject.h"
class BasicObject : public SceneObject
{
private:
	Vector3 _position;
	GLfloat _rotation;
	Material* _material;
	GLfloat rotationx;
	GLfloat rotationy;
	GLfloat rotationz;

public:
	BasicObject(Mesh* mesh, Texture2D* texture, float x, float y, float z);
	~BasicObject();
	void Draw();
	void Update();
	void InitMaterials();
	void Rotate(GLfloat rotx, GLfloat roty, GLfloat rotz);
	Vector3 GetPos();
};

