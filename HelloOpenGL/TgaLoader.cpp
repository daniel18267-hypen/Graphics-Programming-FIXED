#include "TgaLoader.h"
int TgaLoader::LoadTGA(const char* path)
{
	id = 0;
	tempheaderdata = new char[18];
	std::ifstream infile;
	infile.open(path, std::ios::binary);
	if (!infile.good())
	{
		std::cerr << "cant open texture file" << std::endl;
		return -1;
	}
	infile.seekg(0, std::ios::beg);
	infile.read(tempheaderdata, 18);
	infile.seekg(0, std::ios::end);
	filesize = (int)infile.tellg() - 18;
	temptexturedata = new char[filesize];
	infile.seekg(18, std::ios::beg);
	infile.read(temptexturedata, filesize);
	infile.close();
	type = tempheaderdata[2];
	width = ((unsigned char)tempheaderdata[13] << 8U) + (unsigned char)tempheaderdata[12];
	height = ((unsigned char)tempheaderdata[15] << 8U) + (unsigned char)tempheaderdata[14];
	pixeldepth = tempheaderdata[16];
	flipped = false;
	if ((int)((tempheaderdata[11] << 8) + tempheaderdata[10]) == 0);
	{
		flipped = true;
	}
	if (type == 2)
	{
		std::cout << path << "loaded" << std::endl;
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);
		mode = pixeldepth / 8;
		if (mode == 4)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, temptexturedata);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, temptexturedata);

		}

	
	}
	delete[] tempheaderdata;
	delete[] temptexturedata;
	return id;
}
