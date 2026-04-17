#include "objectloader.h"
std::vector<Vertex>* objectloader::indexedvertices = new std::vector<Vertex>;
std::vector<Vertex>* objectloader::faces = new std::vector<Vertex>;
int objectloader::numvertices = 0;
int objectloader::numfaces = 0;
int objectloader::mode = 0;
int objectloader::vertexindex = 0;
int objectloader::facesindex = 1;
int objectloader::loopcount = 1;
int objectloader::facecount = 1;
int objectloader::vertexcount = 0;
char objectloader::currentcharacter = 'a';
void objectloader::Draw()
{
	if (indexedvertices != nullptr && faces != nullptr)
	{
		glBegin(GL_TRIANGLES);
		for (int i = 0; i < facecount; i++)
		{
			//glVertex3f(indexedvertices(faces[i]);
		}
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
	while (inFile.eof())
	{
		inFile >> currentcharacter;
		float x, y, z;
		loopcount++;
		std::cout << loopcount;
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
				inFile >> x >> y >> z;
				indexedvertices->push_back({ x, y, z });
			}
			break;
			case 2:
			{
				inFile >> x >> y >> z;
				indexedvertices->push_back({ x,y,z });
				facecount++;
			}
			break;
			}

		
	}
	

	inFile.close();
	return true;

}
