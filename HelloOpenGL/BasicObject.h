#pragma once
#include "SceneObject.h"
class BasicObject : public SceneObject
{
private:
	Vector3 _position;
	GLfloat _rotation;

public:
	BasicObject(Mesh* mesh, Texture2D* texture, float x, float y, float z);
	~BasicObject();
	void Draw();
	void Update();
};

