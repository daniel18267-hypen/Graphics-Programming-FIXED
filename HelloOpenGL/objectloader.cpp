#include "objectloader.h"
std::vector<Vertex>* objectloader::indexedvertices = nullptr;
Vertex* objectloader::faces = nullptr;
int objectloader::numvertices = 0;
int objectloader::numfaces = 0;
int objectloader::mode = 0;
int objectloader::vertexindex = 0;
int objectloader::facesindex = 1;
int objectloader::loopcount = 1;
char objectloader::currentcharacter = 'a';
void objectloader::Draw()
{
	if (indexedvertices != nullptr && faces != nullptr)
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, indexedvertices);
		glPushMatrix();
		glTranslatef(_position.x, _position.y, _position.z);
		glRotatef(_rotation, 1.0f, 0.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, faces);
		glPopMatrix();
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}

objectloader::objectloader(float x, float y, float z)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;
	_rotation = 0.0f;
}
objectloader::~objectloader()
{

}
void objectloader::Update()
{
	_rotation += 0.5f;
}

bool objectloader::Load(char* path)
{
	std::ifstream inFile;
	inFile.open(path);
	if (!inFile.good())
	{
		std::cerr << "Can't open text file" << path << std::endl;
		return false;
	}
	while (!inFile.eof())
	{
		loopcount++;
		std::cout << loopcount;
		inFile >> currentcharacter;
		if (currentcharacter == 'v')
		{
			mode = 1;

		}
		else if (currentcharacter == 'f')
		{

			mode = 2;
		}
		else
			switch (mode)
			{
			case 1:
			{
				{
					
				}
			}
			case 2:
			{
				{
					inFile >> faces[facesindex].x;
					inFile >> faces[facesindex].y;
					inFile >> faces[facesindex].z;
					facesindex++;
				}
			}
			}
	}

	inFile.close();
	return true;

}
