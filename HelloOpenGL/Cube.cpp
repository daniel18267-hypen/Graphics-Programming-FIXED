#include "Cube.h"

void Cube::Draw() 
{
	if (_mesh->Vertices != nullptr && _mesh->Normals != nullptr  &&  _mesh->Indices != nullptr)
	{
		glBindTexture(GL_TEXTURE_2D, _texture->GetID());
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
		glNormalPointer(GL_FLOAT, 0, _mesh->Normals);
		glTexCoordPointer(2, GL_FLOAT, 0, _mesh->Texcoords);
		Cube::InitMaterials();
		glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->ambient.x));
		glMaterialfv(GL_FRONT, GL_DIFFUSE, &(_material->diffuse.x));
		glMaterialfv(GL_FRONT, GL_SPECULAR, &(_material->specular.x));
		glMaterialf(GL_FRONT, GL_SHININESS, _material->shininess);
		glPushMatrix();
		glTranslatef(_position.x, _position.y, _position.z);
		glRotatef(_rotation, 1.0f, 0.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, _mesh->Indices);
		glPopMatrix();
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
}
void Cube::Update()
{
	_rotation += 0.5f;
}
void Cube::InitMaterials()
{
	_material = new Material();
	_material->ambient.x = 0.8f; _material->ambient.y = 0.05f; _material->ambient.z = 0.05f;
	_material->ambient.w = 1.0f;
	_material->diffuse.x = 0.8f; _material->diffuse.y = 0.05f; _material->diffuse.z = 0.05f;
	_material->diffuse.w = 1.0f;
	_material->specular.x = 1.0f; _material->specular.y = 1.0f; _material->specular.z = 1.0f;
	_material->specular.w = 1.0f;
	_material->shininess = 100.0f;
}
Cube::Cube(Mesh* mesh, Texture2D* texture, float x, float y, float z) : SceneObject(mesh, texture)
{
	
	_position.x = x;
	_position.y = y;
	_position.z = z;
	_rotation = 0.0f;
}
Cube::~Cube()
{
	
}
