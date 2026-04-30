#include "BasicObject.h"
BasicObject::BasicObject(Mesh* mesh,Texture2D* texture,float x, float y, float z) : SceneObject(mesh,texture)
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
	/*glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
	glPushMatrix();
	glTranslatef(_position.x, _position.y, _position.z);
	glDrawElements(GL_TRIANGLES, _mesh->IndexCount, GL_UNSIGNED_SHORT, _mesh->Indices);
	glPopMatrix();
	glDisableClientState(GL_VERTEX_ARRAY);
	*/
	if (_texture != nullptr)
	{
		glBindTexture(GL_TEXTURE_2D, _texture->GetID());
	}
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
	glNormalPointer(GL_FLOAT, 0, _mesh->Normals);
	glTexCoordPointer(2, GL_FLOAT, 0, _mesh->Texcoords);
	glPushMatrix();
	glTranslatef(_position.x, _position.y, _position.z);
	glRotatef(_rotation, 1.0f, 0.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, _mesh->IndexCount, GL_UNSIGNED_SHORT, _mesh->Indices);
	glPopMatrix();
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
void BasicObject::Update()
{
	_rotation += 90.0f;
}
