#include <font.h>

namespace ZWET
{
    Font::Font(std::string fontFilePath, std::string fontPicturePath, int windowHeight, int windowWidth, float scale)
    	:fontFilePath(fontFilePath), fontPicturePath(fontPicturePath), windowWidth(windowWidth), 
        windowHeight(windowHeight), scale(scale), lineHeight(0), maxLineWidth(500)
    {
    	readFontFile();
    	convertToUV();
    }

    Font::~Font()
    {
    	;
    }

    void Font::setLineWidth(int width)
    {
    	maxLineWidth = width;
    }

    void Font::setScale(float newScale)
    {
    	scale = newScale;
    }

    mesh Font::convertString(std::string text) //append a string to the class to be rendered
    {
    	std::reverse(text.begin(), text.end());

    	return calculateMesh(text);
    }

    void Font::convertToUV() //converts the data to uvs on the texture
    {
    	//loop trough all of the characters
    	for (const auto& it : charMap)
    	{
    		CharInfo charData = it.second;
    
    		//translate the coordinate pixel data to UV data uv is from 0-1 starting in the bottom left corner
    		charData.UV[2] = { (float)charData.x / (float)imageResolution[0], 1.0f - ((float)charData.y + (float)charData.height ) / (float)imageResolution[1] }; // bottom left
    		charData.UV[3] = { (float)charData.x / (float)imageResolution[0], 1.0f - (float)charData.y / (float)imageResolution[0] }; // top left
    		charData.UV[0] = { ((float)charData.x + (float)charData.width) / (float)imageResolution[0], 1.0f - ((float)charData.y + (float)charData.height) / (float)imageResolution[1] }; // bottom right
    		charData.UV[1] = { ((float)charData.x + (float)charData.width) / (float)imageResolution[0], 1.0f - (float)charData.y / (float)imageResolution[1]}; // top right

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
    			s >> sJunk >> cJunk >> cJunk >> cJunk >> cJunk >> cJunk >> cJunk >> cJunk >> cJunk >> cJunk >> cJunk >> cJunk >> lineHeight;
    			s >> sJunk;
    			s >> cJunk >> cJunk >> cJunk >> cJunk >> cJunk >> cJunk >> cJunk >> imageResolution[0]; //width of the font sprite
    			s >> cJunk >> cJunk >> cJunk >> cJunk >> cJunk >> cJunk >> cJunk >> imageResolution[1]; //height of the font sprite
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

    mesh Font::calculateMesh(std::string text) //create the text mesh
    {
    	mesh fontMesh; // mesh the font is gonna be stored in
    	vec3 pixSize = { (float)windowWidth / 200.0f, (float)windowHeight / 200.0f, 0.0f }; // calculate the pixel size
    	float lineWidth = 0; // current line width
    	vec2 cursorPos = {0.0f, 0.0f}; //cursor positon

    	for (int i = 0; i < text.length(); i++)
    	{
    		CharInfo currChar = charMap[(int)text[i]];

    		/*
    			verticies go counter clockvise
    		*/


    		vec3 vert1 = { // bottom left
    			cursorPos.x + currChar.xoffset,
    			cursorPos.y,
    			0.0f
    		};

    		vec3 vert2 = { // top left
    			cursorPos.x + currChar.xoffset,
    			cursorPos.y + 71.0f-currChar.yoffset,
    			0.0f
    		};

    		vec3 vert3 = { // top right
    			cursorPos.x + currChar.xadvance,
    			cursorPos.y + 71.0f-currChar.yoffset,
    			0.0f
    		};

    		vec3 vert4 = { // bottom right
    			cursorPos.x + currChar.xadvance,
    			cursorPos.y,
    			0.0f
    		};

    		vert1 = vert1 * scale;
    		vert2 = vert2 * scale;
    		vert3 = vert3 * scale;
    		vert4 = vert4 * scale;

    		fontMesh.tris.push_back({
    			{ vert3, vert1, vert4 }, { currChar.UV[3], currChar.UV[0], currChar.UV[2] }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }
    			});

    		fontMesh.tris.push_back({
    			{ vert3, vert2, vert1 }, { currChar.UV[3], currChar.UV[1], currChar.UV[0] }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }
    			});

    		cursorPos.x += currChar.xadvance;

    		if (lineWidth + charMap[(int)text[i + 1]].xadvance > maxLineWidth)
    		{
    			cursorPos.y -= lineHeight;
    			lineWidth = 0;
    		}
    	}

        return fontMesh;
    }
}