#include "SceneObject.h"
SceneObject::SceneObject(Mesh* mesh, Texture2D* texture)
{
	_mesh = mesh;
	_texture = texture;
	
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
void SceneObject::Rotate(GLfloat rotx, GLfloat roty, GLfloat rotz)
{

}
Vector3 SceneObject::GetPos()
{
	return Vector3();
}