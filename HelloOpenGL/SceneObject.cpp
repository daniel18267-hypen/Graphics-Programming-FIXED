#include "SceneObject.h"
// just a class that other classes inherit from for polymorphism purposes (so can call same functions for all the different classes)
// however only have one thing that inherits from it, being the basicobject class, didn't need anything else for my simulation.
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
void SceneObject::Rotate(GLfloat rotx, GLfloat roty, GLfloat rotz,int direction)
{

}
void SceneObject::IsSelected()
{

}
Vector3 SceneObject::GetPos()
{
	return Vector3();
}