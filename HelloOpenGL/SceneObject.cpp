#include "SceneObject.h"
SceneObject::SceneObject(Mesh* mesh, Texture2D* texture)
{
	_mesh = mesh;
	if (texture)
	{
		_texture = texture;
	}
}
SceneObject::~SceneObject()
{

}
void SceneObject::Update()
{

}
void SceneObject::Draw()
{

}
void SceneObject::InitMaterials()
{

}