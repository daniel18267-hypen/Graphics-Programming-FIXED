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
	void AdvancedLoadTexCoords(ifstream& inFile, Mesh& mesh);
	void AdvancedLoadNormals(ifstream& inFile, Mesh& mesh);

	void AdvancedLoadTexCoords(ifstream& inFile, Mesh& mesh)
	{
		int texcoordindex = 0;
		string line;

		while (std::getline(inFile, line))
		{

			string prefix;
			stringstream ss(line);
			ss >> prefix;
			//char currentcharacter;
			//inFile >> currentcharacter;



			if (prefix == "vt")
			{
				ss >> mesh.Texcoords[texcoordindex].u;
				ss >> mesh.Texcoords[texcoordindex].v;

				texcoordindex++;
			}
		}
		inFile.clear();
		inFile.seekg(0);
	}
	void AdvancedLoadNormals(ifstream& inFile, Mesh& mesh)
	{
		int normalindex = 0;
		string line;
		while (std::getline(inFile, line))
		{
			string prefix;
			stringstream ss(line);
			ss >> prefix;
			if (prefix == "vn")
			{
				ss >> mesh.Normals[normalindex].x;
				ss >> mesh.Normals[normalindex].y;
				ss >> mesh.Normals[normalindex].z;
				normalindex++;

			}
		}
		inFile.clear();
		inFile.seekg(0);
	}
	void AdvancedLoadTextFaces(ifstream& inFile, Mesh& mesh)
	{
		int faceindex = 0;
		int position;
		int position1;
		int position2;
		string line;
		while (std::getline(inFile, line))
		{
			string prefix;
			string vertex, vertex1, vertex2;
			int vertexpos;
			int texcoordpos;
			int normalpos;
			IndexedVertices vertices;
			stringstream ss(line);
			
			ss >> prefix;
			if (prefix == "f")
			{
				ss >> vertex >> vertex1 >> vertex2;
				position = vertex.find('/');
				vertexpos = stoi(vertex.substr(0, position));
				position1 = vertex.find('/', position + 1);
				texcoordpos = stoi(vertex.substr(position + 1, (position1 - position - 1)));
				normalpos = stoi(vertex.substr(position1 + 1));
				vertices.Position = mesh.Vertices[vertexpos - 1];
				vertices.Normals = mesh.Normals[normalpos - 1];
				vertices.Texcoords = mesh.Texcoords[texcoordpos - 1];
				mesh.IndexedVertices[faceindex] = vertices;
				mesh.Indices[faceindex] = faceindex;
				faceindex++;

				position = vertex1.find('/');
				vertexpos = stoi(vertex1.substr(0, position));
				position1 = vertex1.find('/', position + 1);
				texcoordpos = stoi(vertex1.substr(position + 1, (position1 - position - 1)));;
				normalpos = stoi(vertex1.substr(position1 + 1));
				vertices.Position = mesh.Vertices[vertexpos - 1];
				vertices.Normals = mesh.Normals[normalpos - 1];
				vertices.Texcoords = mesh.Texcoords[texcoordpos - 1];
				mesh.IndexedVertices[faceindex] = vertices;
				mesh.Indices[faceindex] = faceindex;
				faceindex++;

				
				position = vertex2.find('/');
				vertexpos = stoi(vertex2.substr(0, position));
				position1 = vertex2.find('/', position + 1);
				texcoordpos = stoi(vertex2.substr(position + 1, (position1 - position - 1)));
				normalpos = stoi(vertex2.substr(position1 + 1));
				vertices.Position = mesh.Vertices[vertexpos - 1];
				vertices.Normals = mesh.Normals[normalpos - 1];
				vertices.Texcoords = mesh.Texcoords[texcoordpos - 1];
				mesh.IndexedVertices[faceindex] = vertices;
				mesh.Indices[faceindex] = faceindex;
				faceindex++;

				
				

				
			}
		}
		inFile.clear();
		inFile.seekg(0);
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
			else if (prefix == "vn")
			{
				mesh.NormalCount++;
			}
			else if (prefix == "vt")
			{
				std::cout << mesh.TexCoordCount << endl;
				mesh.TexCoordCount++;
			} 
		}
		mesh.Vertices = new Vertex[mesh.VertexCount];
		mesh.IndexedVertices = new IndexedVertices[mesh.IndexCount];
		mesh.Indices = new GLushort[mesh.IndexCount];
		mesh.Normals = new Vector3[mesh.NormalCount];
		mesh.Texcoords = new TexCoord[mesh.TexCoordCount];
		inFile.clear();
		inFile.seekg(0);
		
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
		mesh->TexCoordCount = 0;
		mesh->NormalCount = 0;
		if (!inFile.good())
		{
			cerr << "Can't open file " << path << endl;
			return nullptr;
		}
		else
		{
			AdvancedInitArrays(inFile , *mesh);
			AdvancedLoadVertices(inFile, *mesh);
			AdvancedLoadTexCoords(inFile, *mesh);
			AdvancedLoadNormals(inFile, *mesh);
			AdvancedLoadTextFaces(inFile, *mesh);
			
			
			
			
			
			std::cerr << mesh->VertexCount;
			std::cerr << mesh->IndexCount;
			inFile.close();
			return mesh;
			
		} 
	
	} 
}