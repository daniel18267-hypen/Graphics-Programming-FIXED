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
	bool isselected;

public:
	BasicObject(Mesh* mesh, Texture2D* texture, float x, float y, float z);
	~BasicObject();
	void Draw();
	void Update();
	void InitMaterials();
	void Rotate(GLfloat rotx, GLfloat roty, GLfloat rotz ,int direction);
	void IsSelected();
	Vector3 GetPos();
};

