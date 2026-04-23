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

	void LoadNormals(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.NormalCount;
		
		if (mesh.NormalCount > 0)
		{
			mesh.Normals = new Vector3[mesh.NormalCount];
			for (int i = 0; i < mesh.NormalCount; i++)
			{
				inFile >> mesh.Normals[i].x;
				inFile >> mesh.Normals[i].y;
				inFile >> mesh.Normals[i].z;
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
			LoadTexCoords(inFile, *mesh);
			LoadNormals(inFile, *mesh);
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
			//LoadColours(inFile, *mesh);
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
		stringstream ss;
		mesh->VertexCount = 0;
		mesh->IndexCount = 0;
		mesh->TexCoordCount = 0;
		mesh->NormalCount = 0;
		if (!inFile.good())
		{
			cerr << "Can't open file " << path << endl;
			return nullptr;
		}
		else
		{
			while (!inFile.eof())
			{
				std::string line;
				std::getline(inFile, line);
				inFile >> line;
				//std::cout << line;
				char currentcharacter;
				inFile >> currentcharacter;
				if (line == "v")
				{
					mesh->VertexCount++;
				}
				else if (line == "f")
				{
					mesh->IndexCount++;
					mesh->IndexCount++;
					mesh->IndexCount++;
				}
				else if (line == "vn")
				{
					mesh->NormalCount++;
				}
				else if (line == "vt")
				{
					mesh->TexCoordCount++;
				}
			}
			inFile.clear();
			inFile.seekg(0);
			mesh->Vertices = new Vertex[mesh->VertexCount];
			mesh->Indices = new GLushort[mesh->IndexCount];
			mesh->Normals = new Vector3[mesh->NormalCount];
			mesh->Texcoords = new TexCoord[mesh->TexCoordCount];
			int vertexindex = 0;
			int faceindex = 0;
			while (!inFile.eof())
			{
				char currentcharacter;
				
				inFile >> currentcharacter;

				if (currentcharacter == 'v')
				{
					inFile >> mesh->Vertices[vertexindex].x;
					inFile >> mesh->Vertices[vertexindex].y;
					inFile >> mesh->Vertices[vertexindex].z;
					vertexindex++;
				}
				if (currentcharacter == 'f')
				{
					inFile >> mesh->Indices[faceindex];
					mesh->Indices[faceindex]--;
					faceindex++;
					inFile >> mesh->Indices[faceindex];
					mesh->Indices[faceindex]--;
					faceindex++;
					inFile >> mesh->Indices[faceindex];
					mesh->Indices[faceindex]--;
					faceindex++;

				}

			}
			std::cerr << mesh->VertexCount;
			std::cerr << mesh->IndexCount;
			inFile.close();
			return mesh;
			
		} 
	
	} 
}