#include "Texture2D.h"
using namespace std;
Texture2D::Texture2D()
{

}
Texture2D::~Texture2D()
{
	glDeleteTextures(1, &_ID);
}
bool Texture2D::Load(char* path, int width, int height)
{
	char* temptexturedata; int filesize; ifstream infile;
	_width = width; _height = height;
	infile.open(path, ios::binary);

	if (!infile.good())
	{
		std::cerr << "Couldn't open texture file";
		return false;
	}
	infile.seekg(0, ios::end);
	filesize = (int)infile.tellg();
	temptexturedata = new char[filesize];
	infile.seekg(0,ios::beg);
	infile.read(temptexturedata, filesize);
	infile.close();

	std::cout << path << "Loaded" << endl;

	glGenTextures(1, &_ID);
	glBindTexture(GL_TEXTURE_2D, _ID);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, temptexturedata);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, temptexturedata);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	delete[] temptexturedata;
	return true;

}