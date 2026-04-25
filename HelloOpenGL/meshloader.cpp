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
	void AdvancedInitArrays(ifstream& inFile, Mesh& mesh);
	void AdvancedLoadVertices(ifstream& inFile, Mesh& mesh);
	void AdvancedLoadBasicFaces(ifstream& inFile, Mesh& mesh);
	void AdvancedLoadTextFaces(ifstream& inFile, Mesh& mesh);
	void AdvancedLoadTextFaces(ifstream& inFile, Mesh& mesh)
	{
		int faceindex = 0;
		string line;
		while (std::getline(inFile, line))
		{
			string prefix;
			string test;
			string throwaway;
			stringstream ss(line);
			
			ss >> prefix;
			while (std::getline(ss,line , '/'))
			{
				if (prefix == "f")
				{
					std::cout << line;

				}
			}
		}
	}
	void AdvancedLoadBasicFaces(ifstream& inFile, Mesh& mesh)
	{
		int faceindex = 0;
		string line;
		while (std::getline(inFile, line))
		{
			std::cout << line;
			string prefix;
			stringstream ss(line);
			ss >> prefix;
			if (prefix == "f")
			{
				ss >> mesh.Indices[faceindex];
				mesh.Indices[faceindex]--;
				faceindex++;
				ss >> mesh.Indices[faceindex];
				mesh.Indices[faceindex]--;
				faceindex++;
				ss >> mesh.Indices[faceindex];
				mesh.Indices[faceindex]--;
				faceindex++;

			}

		}
		inFile.clear();
		inFile.seekg(0);
	}
	void AdvancedLoadVertices(ifstream& inFile, Mesh& mesh)
	{
		int vertexindex = 0;
		int faceindex = 0;
		string line;
		
		while (std::getline(inFile,line))
		{
			
			string prefix;
			stringstream ss(line);
			ss >> prefix;
			//char currentcharacter;
			//inFile >> currentcharacter;



			if (prefix == "v")
			{
				ss >> mesh.Vertices[vertexindex].x;
				ss >> mesh.Vertices[vertexindex].y;
				ss >> mesh.Vertices[vertexindex].z;
				vertexindex++;
			}
			/* if (currentcharacter == 'f')
			{
				inFile >> mesh.Indices[faceindex];
				mesh.Indices[faceindex]--;
				faceindex++;
				inFile >> mesh.Indices[faceindex];
				mesh.Indices[faceindex]--;
				faceindex++;
				inFile >> mesh.Indices[faceindex];
				mesh.Indices[faceindex]--;
				faceindex++;

			} */
			
			

		}
		inFile.clear();
		inFile.seekg(0);
	}
	void AdvancedInitArrays(ifstream& inFile, Mesh& mesh)
	{	
		string line;
		while (std::getline(inFile,line))
		{
			string prefix;
			stringstream ss(line);
			ss >> prefix;
			if (prefix == "v")
			{
				mesh.VertexCount++;
			}
			else if (prefix == "f")
			{
				mesh.IndexCount++;
				mesh.IndexCount++;
				mesh.IndexCount++;
			}
			else if (line == "vn")
			{
				mesh.NormalCount++;
			}
			else if (line == "vt")
			{
				mesh.TexCoordCount++;
			} 
		}

		inFile.clear();
		inFile.seekg(0);
		mesh.Vertices = new Vertex[mesh.VertexCount];
		mesh.Indices = new GLushort[mesh.IndexCount];
		//mesh->Normals = new Vector3[mesh->NormalCount];
		//mesh->Texcoords = new TexCoord[mesh->TexCoordCount];
	}
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
		stringstream ss;
		inFile.open(path);
		
		mesh->VertexCount = 0;
		mesh->IndexCount = 0;
		//mesh->TexCoordCount = 0;
		//mesh->NormalCount = 0;
		if (!inFile.good())
		{
			cerr << "Can't open file " << path << endl;
			return nullptr;
		}
		else
		{
			AdvancedInitArrays(inFile , *mesh);
			AdvancedLoadVertices(inFile, *mesh);
			//AdvancedLoadBasicFaces(inFile, *mesh);
			AdvancedLoadTextFaces(inFile, *mesh);
			
			std::cerr << mesh->VertexCount;
			std::cerr << mesh->IndexCount;
			inFile.close();
			return mesh;
			
		} 
	
	} 
}