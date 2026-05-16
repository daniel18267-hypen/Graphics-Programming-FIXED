#include "meshloader.h"
#include "Structures.h"

#include <iostream>
#include <fstream>

using namespace std;

namespace MeshLoader
{
	// initialises functions
	void InitArrays(ifstream& inFile, Mesh& mesh);
	void LoadVertices(ifstream& inFile, Mesh& mesh);
	void LoadFaces(ifstream& inFile, Mesh& mesh);
	void LoadTexCoords(ifstream& inFile, Mesh& mesh);
	void LoadNormals(ifstream& inFile, Mesh& mesh);
	/// <summary>
	/// loads texture coordinates.
	/// </summary>
	/// <param name="inFile"></param>
	/// <param name="mesh"></param>
	void LoadTexCoords(ifstream& inFile, Mesh& mesh)
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
	void LoadNormals(ifstream& inFile, Mesh& mesh)
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
	/// <summary>
	/// loads faces and then constructs vertices with the face data.
	/// </summary>
	/// <param name="inFile"></param>
	/// <param name="mesh"></param>
	void LoadFaces(ifstream& inFile, Mesh& mesh)
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
				// reads the three vertexes that make up a face line and stores them in variable
				ss >> vertex >> vertex1 >> vertex2;
				// finds the "/" that separates each section of the face data.
				position = vertex.find('/');
				// makes a substring extracting the vertex data, converting to integer and storing it
				vertexpos = stoi(vertex.substr(0, position));
				// finds the next "/" after the first one
				position1 = vertex.find('/', position + 1);
				// makes two new substrings, one with the texcoord data and one with the normal data and converting to integer and storing it.
				texcoordpos = stoi(vertex.substr(position + 1, (position1 - position - 1)));
				normalpos = stoi(vertex.substr(position1 + 1));
				// we then look up the positions we extracted from face data, use them to get data from the arrays made earlier and store in vertices struct
				vertices.Position = mesh.Vertices[vertexpos - 1];
				vertices.Normals = mesh.Normals[normalpos - 1];
				vertices.Texcoords = mesh.Texcoords[texcoordpos - 1];
				// then store the vertices in the array
				mesh.IndexedVertices[faceindex] = vertices;
				// then store the indices value in indices array and increase it - note this isn't the most optimal way of doing things and could be improved
				mesh.Indices[faceindex] = faceindex;
				faceindex++;
				 // we then repeat this 2 times for the next 2 faces on the line.
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
		// clear and go back to 0.
		inFile.clear();
		inFile.seekg(0);
	}
	/// <summary>
	/// If first part of string is v, loads the rest of the string into the vertices array.
	/// </summary>
	/// <param name="inFile"></param>
	/// <param name="mesh"></param>
	void LoadVertices(ifstream& inFile, Mesh& mesh)
	{
		int vertexindex = 0;
		string line;
		
		while (std::getline(inFile,line))
		{
			
			string prefix;
			stringstream ss(line);
			ss >> prefix;
			
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
	/// <summary>
	/// loops through the file, adds to the count for respective prefix, intialises array of that size that the data then can go in
	/// </summary>
	/// <param name="inFile"></param>
	/// <param name="mesh"></param>
	void InitArrays(ifstream& inFile, Mesh& mesh)
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
	/// <summary>
	/// Initialises variables, opens file and calls function to load a standard waverfront .obj file, then closes file and returns mesh.
	/// </summary>
	/// <param name="path"></param>
	/// <returns></returns>
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
			InitArrays(inFile , *mesh);
			LoadVertices(inFile, *mesh);
			LoadTexCoords(inFile, *mesh);
			LoadNormals(inFile, *mesh);
			LoadFaces(inFile, *mesh);
			inFile.close();
			return mesh;
			
		} 
	
	} 
}