#include "BasicObject.h"
BasicObject::BasicObject(Mesh* mesh, float x, float y, float z) : SceneObject(mesh, nullptr)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;
	_rotation = 0.0f;
}
BasicObject:: ~BasicObject()
{

}
void BasicObject::Draw()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
	glPushMatrix();
	glDrawElements(GL_TRIANGLES, _mesh->IndexCount, GL_UNSIGNED_SHORT, _mesh->Indices);
	glPopMatrix();
	glDisableClientState(GL_VERTEX_ARRAY);
}
void BasicObject::Update()
{

}
