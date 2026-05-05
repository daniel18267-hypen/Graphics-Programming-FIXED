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
	BasicObject::InitMaterials();
	glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->ambient.x));
	glMaterialfv(GL_FRONT, GL_DIFFUSE, &(_material->diffuse.x));
	glMaterialfv(GL_FRONT, GL_SPECULAR, &(_material->specular.x));
	glMaterialf(GL_FRONT, GL_SHININESS, _material->shininess);
	glPushMatrix();
	glTranslatef(_position.x, _position.y, _position.z);
	glRotatef(_rotation, rotationx,rotationy,rotationz);
	glDrawElements(GL_TRIANGLES, _mesh->IndexCount, GL_UNSIGNED_SHORT, _mesh->Indices);
	glPopMatrix();
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
void BasicObject::Update()
{
	if (!isselected)
	{
		_rotation += 5.0f;
		rotationx = 1.0f;
	}
	//_position.x += 0.5f;
}
void BasicObject::Rotate(GLfloat rotx, GLfloat roty, GLfloat rotz ,int direction)
{
	
	rotationx = rotx;
	rotationy = roty;
	
	rotationz = rotz;
	std::cout << rotationx << std::endl << rotationy << std::endl << rotationz << std::endl;
	_rotation += 2.0f * direction;
}
Vector3 BasicObject::GetPos()
{
	return _position;
}
void BasicObject::InitMaterials()
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
void BasicObject::IsSelected()
{
	isselected = !isselected;
}
