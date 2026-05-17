#include "Texture2D.h"
// constructor and destructor
Texture2D::Texture2D()
{

}
Texture2D::~Texture2D()
{
	glDeleteTextures(1, &ID);
}
/// <summary>
/// loads tga texture from file
/// </summary>
/// <param name="path"></param>
/// <returns></returns>
int Texture2D::Load(const char* path)
{
	ID = 0;
	// header data is 18 chars long
	tempheaderdata = new char[18];
	// opens file, if file isn't valid outputs error message
	std::ifstream infile;
	infile.open(path, std::ios::binary);
	if (!infile.good())
	{
		std::cerr << "cant open texture file" << std::endl;
		return -1;
	}
	// starts from beginning, reads first 18 characters into the tempheaderdata array.
	infile.seekg(0, std::ios::beg);
	infile.read(tempheaderdata, 18);
	// goes back to end of file
	infile.seekg(0, std::ios::end);
	// gets file size by getting position of pointer and subtracting 18 (size of header data)
	filesize = (int)infile.tellg() - 18;
	// allocates texture data to be an array of file size
	temptexturedata = new char[filesize];
	// goes to start of actual data, skips header data, and reads it into temptexturedata array
	infile.seekg(18, std::ios::beg);
	infile.read(temptexturedata, filesize);
	// close file
	infile.close();
	// gets info from header data
	type = tempheaderdata[2];
	width = ((unsigned char)tempheaderdata[13] << 8U) + (unsigned char)tempheaderdata[12];
	height = ((unsigned char)tempheaderdata[15] << 8U) + (unsigned char)tempheaderdata[14];
	pixeldepth = tempheaderdata[16];
	flipped = false;
	if ((int)((tempheaderdata[11] << 8) + tempheaderdata[10]) == 0);
	{
		flipped = true;
	}
	// acts on that info depending on what type / mode it is, note this hasn't been expanded upon and could do with more work to make it more flexible
	if (type == 2)
	{
		std::cout << path << "loaded" << std::endl;
		// generates and binds texture
		glGenTextures(1, &ID);
		glBindTexture(GL_TEXTURE_2D, ID);
		// enables mipmaps
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, temptexturedata);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		mode = pixeldepth / 8;
		// essentially, if mode == 4 this means its 32 bit and uses blue, green red and alpha, if its not it just uses blue, green and red.
		if (mode == 4)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, temptexturedata);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, temptexturedata);

		}


	}
	// deletes texture
	delete[] tempheaderdata;
	delete[] temptexturedata;
	return ID;
}