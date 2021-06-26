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
	//loop trough all of the characters
	for (const auto& it : charMap)
	{
		CharInfo charData = it.second;
		
		//translate the coordinate pixel data to UV data uv is from 0-1 starting in the bottom left corner
		charData.UV[0] = {1-(charData.x/imageResolution[0]), 1-(charData.y+charData.height/imageResolution[1])};
		charData.UV[1] = {1-(charData.x/imageResolution[0]), 1-(charData.y/imageResolution[1])};
		charData.UV[2] = {1-(charData.x+charData.width/imageResolution[0]), 1-(charData.y+charData.height/imageResolution[1])};
		charData.UV[3] = {1-(charData.x+charData.width/imageResolution[0]), 1-(charData.y/imageResolution[1])};

		charMap[charData.id] = charData;
	}
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

		char cJunk;
		std::string sJunk;

		if (line[0] == 'c' && line[1] == 'o')
		{
			s >> sJunk >> sJunk >> sJunk;
			s >> cJunk >> cJunk >> cJunk >> cJunk >> cJunk >> cJunk >> imageResolution[0];
			s >> cJunk >> cJunk >> cJunk >> cJunk >> cJunk >> cJunk >> imageResolution[1];
		}
		
		if (line[0] == 'c' && line[1] == 'h' && line[4] != 's')
		{
			CharInfo currChar;

			s >> sJunk >> cJunk >> cJunk >> cJunk >> currChar.id;
			s >> cJunk >> cJunk >> currChar.x;
			s >> cJunk >> cJunk >> currChar.y;
			s >> cJunk >> cJunk >> cJunk >> cJunk >> cJunk >> cJunk >> currChar.width;
			s >> cJunk >> cJunk >> cJunk >> cJunk >> cJunk >> cJunk >> cJunk >> currChar.height;
			s >> cJunk >> cJunk >> cJunk >> cJunk >> cJunk >> cJunk >> cJunk >> cJunk >> currChar.xoffset;
			s >> cJunk >> cJunk >> cJunk >> cJunk >> cJunk >> cJunk >> cJunk >> cJunk >> currChar.yoffset;
			s >> cJunk >> cJunk >> cJunk >> cJunk >> cJunk >> cJunk >> cJunk >> cJunk >> cJunk >> currChar.xadvance;

			charMap.insert(std::pair<int, CharInfo>(currChar.id, currChar));
		}
	}
}

void Font::calculateMesh() //calculate the size of the mesh
{

}