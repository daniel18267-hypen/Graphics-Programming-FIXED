#include "meshloader.h"
#include "Structures.h"

#include <iostream>
#include <fstream>

using namespace std;

namespace MeshLoader
{
	void LoadVertices(ifstream& inFile, Mesh& mesh);
	void LoadColours(ifstream& inFile, Mesh& mesh);
	void LoadIndices(ifstream& inFile, Mesh& mesh);
	void LoadTexCoords(ifstream& inFile, Mesh& mesh);

	void LoadVertices(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.VertexCount;

		if (mesh.VertexCount > 0)
		{
			mesh.Vertices = new Vertex[mesh.VertexCount];

			for (int i = 0; i < mesh.VertexCount; i++)
			{
				inFile >> mesh.Vertices[i].x;
				inFile >> mesh.Vertices[i].y;
				inFile >> mesh.Vertices[i].z;
			}
		}
	}

	void LoadColours(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.ColorCount;
		if (mesh.ColorCount > 0)
		{
			mesh.Colors = new Color[mesh.ColorCount];
			for (int i = 0; i < mesh.ColorCount; i++)
			{
				inFile >> mesh.Colors[i].r;
				inFile >> mesh.Colors[i].g;
				inFile >> mesh.Colors[i].b;
			}
		}
	}
	void LoadTexCoords(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.TexCoordCount;
		if (mesh.TexCoordCount > 0)
		{
			mesh.Texcoords = new TexCoord[mesh.TexCoordCount];
			for (int i = 0; i < mesh.TexCoordCount; i++)
			{
				inFile >> mesh.Texcoords[i].u;
				inFile >> mesh.Texcoords[i].v;
			}
		}
	}

	void LoadIndices(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.IndexCount;

		if (mesh.IndexCount > 0)
		{
			mesh.Indices = new GLushort[mesh.IndexCount];
			for (int i = 0; i < mesh.IndexCount; i++)
			{
				inFile >> mesh.Indices[i];
			}
		}
	}

	Mesh* MeshLoader::LoadTextured(const char* path)
	{
		Mesh* mesh = new Mesh();

		ifstream inFile;

		inFile.open(path);

		if (!inFile.good())
		{
			cerr << "Can't open file" << path << endl;
			return nullptr;
		}
		else
		{
			LoadVertices(inFile, *mesh);
			LoadColours(inFile, *mesh);
			LoadTexCoords(inFile, *mesh);
			LoadIndices(inFile, *mesh);
		}
		inFile.close();
		return mesh;
	}
	Mesh* MeshLoader::Load(const char* path)
	{
		Mesh* mesh = new Mesh();

		ifstream inFile;

		inFile.open(path);

		if (!inFile.good())
		{
			cerr << "Can't open  file " << path << endl;
			return nullptr;
		}
		else
		{
			LoadVertices(inFile, *mesh);
			LoadColours(inFile, *mesh);
			LoadIndices(inFile, *mesh);
		}
		inFile.close();
		return mesh;
	}
	Mesh* MeshLoader::LoadAdvanced(const char* path)
	{
		Mesh* mesh = new Mesh();
		ifstream inFile;
		inFile.open(path);
		mesh->VertexCount = 0;
		mesh->IndexCount = 0;
		if (!inFile.good())
		{
			cerr << "Can't open file " << path << endl;
			return nullptr;
		}
		else
		{
			while (!inFile.eof())
			{
				char currentcharacter;
				inFile >> currentcharacter;
				if (currentcharacter == 'v')
				{
					mesh->VertexCount++;
				}
				else if (currentcharacter == 'f')
				{
					mesh->IndexCount++;
				}
			}
			inFile.clear();
			inFile.seekg(0);
			mesh->Vertices = new Vertex[mesh->VertexCount];
			mesh->Indices = new GLushort[mesh->IndexCount];

			while (!inFile.eof())
			{
				for (int i = 0; i < mesh->VertexCount; i++)
				{
					char throwaway;
					inFile >> throwaway;
					inFile >> mesh->Vertices[i].x;
					inFile >> mesh->Vertices[i].y;
					inFile >> mesh->Vertices[i].z;
				}
				for (int i = 0; i < mesh->IndexCount; i++)
				{
					char throwaway;
					inFile >> throwaway;
					inFile >> mesh->Indices[i];


				}

			}
			
			std::cerr << mesh->VertexCount;
			std::cerr << mesh->IndexCount;
			inFile.close();
			return mesh;
		}
	}
}