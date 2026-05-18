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
/// <summary>
/// draws the object using gldrawelements, with normals and textures.
/// </summary>
void BasicObject::Draw()
{
	
	if (_texture != nullptr)
	{
		glBindTexture(GL_TEXTURE_2D, _texture->GetID());
	}
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY); 
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(IndexedVertices), &_mesh->IndexedVertices[0].Position);
	glNormalPointer(GL_FLOAT, sizeof(IndexedVertices), &_mesh->IndexedVertices[0].Normals);
	glTexCoordPointer(2, GL_FLOAT, sizeof(IndexedVertices), &_mesh->IndexedVertices[0].Texcoords);
	BasicObject::InitMaterials();
	glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->ambient.x));
	glMaterialfv(GL_FRONT, GL_DIFFUSE, &(_material->diffuse.x));
	glMaterialfv(GL_FRONT, GL_SPECULAR, &(_material->specular.x));
	glMaterialf(GL_FRONT, GL_SHININESS, _material->shininess);
	glPushMatrix();
	glTranslatef(_position.x, _position.y, _position.z);
	glRotatef(_rotation, rotationx,rotationy,rotationz);
	glDrawElements(GL_TRIANGLES, _mesh->IndexCount, GL_UNSIGNED_INT, _mesh->Indices);
	glPopMatrix();
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
/// <summary>
/// called every frame
/// </summary>
void BasicObject::Update()
{
	// rotates if not selected by user
	if (!isselected)
	{
		_rotation += 5.0f;
		rotationx = 1.0f;
	}
}
/// <summary>
/// used for user  controlled rotation
/// </summary>
/// <param name="rotx"></param>
/// <param name="roty"></param>
/// <param name="rotz"></param>
/// <param name="direction"></param>
void BasicObject::Rotate(GLfloat rotx, GLfloat roty, GLfloat rotz ,int direction)
{
	
	rotationx = rotx;
	rotationy = roty;
	
	rotationz = rotz;
	_rotation += 2.0f * direction;
}
/// <summary>
/// returns position, used for object tracking camera.
/// </summary>
/// <returns></returns>
Vector3 BasicObject::GetPos()
{
	return _position;
}
/// <summary>
/// Initialises material for the object using material struct
/// </summary>
void BasicObject::InitMaterials()
{
	_material = new Material();
	_material->ambient.x = 1.0f; _material->ambient.y = 1.0f; _material->ambient.z = 1.0f;
	_material->ambient.w = 1.0f;
	_material->diffuse.x = 0.8f; _material->diffuse.y = 0.05f; _material->diffuse.z = 0.05f;
	_material->diffuse.w = 1.0f;
	_material->specular.x = 1.0f; _material->specular.y = 1.0f; _material->specular.z = 1.0f;
	_material->specular.w = 1.0f;
	_material->shininess = 100.0f;
}
/// <summary>
/// Called when material is/isnt selected by user. if selected doesn't rotate on it's own
/// </summary>
void BasicObject::IsSelected()
{
	isselected = !isselected;
}
void BasicObject::ChangeTexture(Texture2D* texture)
{
	_texture = texture;
}