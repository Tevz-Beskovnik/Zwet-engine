#pragma once
#include<string>
#include<iostream>
#include<vector>
#include<sstream>
#include<fstream>
#include "../includes/gameObj.h"
#include "../includes/vecs.h"

typedef struct CharInfo
{
	char name; //the char it represents
	int id; //char id (have to find what the ids of chars are)
	int x; //location of start of char (topleft of the char)
	int y;
	int width; //width and height of the char
	int height;
	int xoffset; //how much to offset the char on both axis
	int yoffset;
	int xadvance; //how much to move forward to the next position to palce the character
	int yadvance;
	vecs::vec2 UV[4]; //UVs for the letter
};

class Font
{
	public:
		Font(std::string fontFilePath, std::string fontPicturePath);

		~Font();

		void appendString(std::string text); //append a string to the class to be rendered

		void appendToObject(ObjectInfo* objectToAppendOnto); //add object to be appended to

	private:
		ObjectInfo* object;
		vecs::mesh fontMesh;
		std::string strToRender;
		std::string fontFilePath;
		std::string fontPicturePath;
		std::map<int, CharInfo> charMap;

		void appendStringToObject(); //append the string to the object

		void convertToUV(); //converts the data to uvs on the texture

		void readFontFile(); //reads the .fnt file

		void calculateMesh(); //calculate the size of the mesh
};