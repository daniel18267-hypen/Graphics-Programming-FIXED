#include "objectloader.h"
#include <fstream>
#include <iostream>

std::vector<Vertex>* Faces = nullptr;
std::vector<Vertex>* Vertices = nullptr;
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
	BasicOBJ* objectloader::LoadBasic(const char* path)
	{
		BasicOBJ* object = new BasicOBJ();
		std::ifstream inFile;
		inFile.open(path);

		if (!inFile.good())
		{
			std::cerr << "OBJ file can't be opened";
			return nullptr;
		}

		else
		{
			while (!inFile.eof())
			{
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
				{
					switch (mode)
					{
					case 1:
						GLfloat x, y, z;
						inFile >> x >> y >> z;
						Vertices->push_back({x,y,z});
						

						break;

					case 2:
						GLfloat x, y, z;
						inFile >> x >> y >> z;
						Faces->push_back({ x,y,z });
						break;
					default:


					}

				}
			}
			return object;
		}

		
	}

