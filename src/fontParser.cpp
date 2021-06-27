#include "../includes/fontParser.h"

Font::Font(std::string fontFilePath, std::string fontPicturePath, int* windowRes, int scale)
	:fontFilePath(fontFilePath), fontPicturePath(fontPicturePath), object(nullptr), currentString(""), 
	windowWidth(windowRes[0]), windowHeight(windowRes[1]), scale(scale), lineHeight(0), maxLineWidth(500)
{
	readFontFile();
}

Font::~Font()
{
	;
}

void Font::setLineWidth(int width)
{
	maxLineWidth = width;
}

void Font::appendString(std::string text) //append a string to the class to be rendered
{
	currentString = text;
	calculateMesh();
}

void Font::appendToObject(ObjectInfo* objectToAppendOnto) //add object to be appended to
{
	object = objectToAppendOnto;
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
		charData.UV[0] = {1-((float)charData.x/ (float)imageResolution[0]), 1-((float)charData.y- (float)charData.height/ (float)imageResolution[1])}; // bottom left
		charData.UV[1] = {1-((float)charData.x/ (float)imageResolution[0]), 1-((float)charData.y/ (float)imageResolution[1])}; // top left
		charData.UV[2] = {1-((float)charData.x+ (float)charData.width/ (float)imageResolution[0]), 1-((float)charData.y- (float)charData.height/ (float)imageResolution[1])}; // bottom right
		charData.UV[3] = {1-((float)charData.x+ (float)charData.width/ (float)imageResolution[0]), 1-((float)charData.y/ (float)imageResolution[1])}; // top right

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
			s >> cJunk >> cJunk >> cJunk >> cJunk >> cJunk >> cJunk >> cJunk >> cJunk >> cJunk >> cJunk >> cJunk >> lineHeight;
			s >> sJunk >> sJunk;
			s >> cJunk >> cJunk >> cJunk >> cJunk >> cJunk >> cJunk >> imageResolution[0]; //width of the font sprite
			s >> cJunk >> cJunk >> cJunk >> cJunk >> cJunk >> cJunk >> imageResolution[1]; //height of the font sprite
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

void Font::calculateMesh() //create the text mesh
{
	fontMesh = {}; //reset the font mesh

	vecs::vec3 pixSize = { (float)WINDOW_WIDTH / 200.0f, (float)WINDOW_HEIGHT / 200.0f, 0.0f }; // calculate the pixel size
	float lineWidth = 0; // current line width
	vecs::vec2 cursorPos = {0.0f, 0.0f}; //cursor positon

	for (int i = 0; i < currentString.length(); i++)
	{
		CharInfo currChar = charMap[(int)currentString[i]];

		/*
			verticies go counter clockvise
		*/
		vecs::vec3 vert1 = { // bottom left
			cursorPos.x + currChar.xoffset,
			cursorPos.y,
			0.0f
		};

		vecs::vec3 vert2 = { // top left
			cursorPos.x + currChar.xoffset,
			cursorPos.y + currChar.yoffset,
			0.0f
		};

		vecs::vec3 vert3 = { // top right
			cursorPos.x + currChar.xadvance,
			cursorPos.y + currChar.yoffset,
			0.0f
		};

		vecs::vec3 vert4 = { // bottom right
			cursorPos.x + currChar.xadvance,
			cursorPos.y,
			0.0f
		};

		vert1 = vert1 * pixSize;
		vert2 = vert2 * pixSize;
		vert3 = vert3 * pixSize;
		vert4 = vert4 * pixSize;

		fontMesh.tris.push_back({
			{ vert1, vert2, vert4 }, { currChar.UV[0], currChar.UV[1], currChar.UV[2] }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f }
			});

		fontMesh.tris.push_back({
			{ vert1, vert4, vert3 }, { currChar.UV[0], currChar.UV[2], currChar.UV[3] }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f }
			});

		cursorPos.x += currChar.xadvance;

		if (lineWidth + charMap[(int)currentString[i + 1]].xadvance > maxLineWidth)
		{
			cursorPos.y -= lineHeight;
			lineWidth = 0;
		}
	}
}