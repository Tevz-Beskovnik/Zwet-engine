#include "../includes/fontParser.h"

Font::Font(std::string fontFilePath, std::string fontPicturePath)
	:fontFilePath(fontFilePath), fontPicturePath(fontPicturePath), object(nullptr), strToRender("")
{
	readFontFile();
}

Font::~Font()
{
	;
}

void Font::appendString(std::string text) //append a string to the class to be rendered
{

}

void Font::appendToObject(ObjectInfo* objectToAppendOnto) //add object to be appended to
{

}

void Font::appendStringToObject() //append the string to the object
{

}

void Font::convertToUV() //converts the data to uvs on the texture
{

}

void Font::readFontFile() //reads the .fnt file
{
	std::ifstream f(fontFilePath);
	if (!f.is_open())
		return;

	while (!f.eof())
	{
		char line[256];
		f.getline(line, 256);

		std::stringstream s;
		s << line;

		char junk;


	}
}

void Font::calculateMesh() //calculate the size of the mesh
{

}