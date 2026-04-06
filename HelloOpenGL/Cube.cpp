#include "Cube.h"
Vertex* Cube::indexedvertices = nullptr;
Color* Cube::indexedcolors = nullptr;
GLushort* Cube::indices = nullptr;
int Cube::numvertices = 0;
int Cube::numcolors = 0;
int Cube::numindices = 0;
void Cube::Draw() 
{
	if (indexedvertices != nullptr && indexedcolors != nullptr && indices != nullptr)
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, indexedvertices);
		glColorPointer(3, GL_FLOAT, 0, indexedcolors);
		glPushMatrix();
		glTranslatef(_position.x, _position.y, _position.z);
		glRotatef(_rotation, 1.0f, 0.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, indices);
		glPopMatrix();
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}
void Cube::Update()
{
	_rotation += 0.5f;
}

Cube::Cube(float x, float y, float z)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;
	_rotation = 0.0f;
}
Cube::~Cube()
{
	
}
bool Cube::Load(char* path)
{
	std::ifstream inFile;
	inFile.open(path);
	if (!inFile.good())
	{
		std::cerr << "Can't open text file" << path << std::endl;
		return false;
	}

	inFile >> numvertices;
	indexedvertices = new Vertex[numvertices];
	for (int i = 0; i < numvertices; i++)
	{
		inFile >> indexedvertices[i].x;
		inFile >> indexedvertices[i].y;
		inFile >> indexedvertices[i].z;
	}
	inFile >> numcolors;
	indexedcolors = new Color[numcolors];
	for (int i = 0; i < numcolors; i++)
	{
		inFile >> indexedcolors[i].r;
		inFile >> indexedcolors[i].g;
		inFile >> indexedcolors[i].b;
	}
	inFile >> numindices;
	indices = new GLushort[numindices];
	for (int i = 0; i < numindices; i++)
	{
		inFile >> indices[i];
	}
	inFile.close();
	return true;

}