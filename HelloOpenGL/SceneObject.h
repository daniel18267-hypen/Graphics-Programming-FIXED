#pragma once
#include "Structures.h"
#include "Texture2D.h"
class SceneObject
{
protected:
	Mesh* _mesh;
	Texture2D* _texture;
public:
	SceneObject(Mesh* mesh, Texture2D* texture);
	virtual ~SceneObject();

	virtual void Update();
	virtual void Draw();
	virtual void Rotate(GLfloat rotx, GLfloat roty, GLfloat rotz);
	virtual void InitMaterials();
	virtual void IsSelected();
	virtual Vector3 GetPos();
};

