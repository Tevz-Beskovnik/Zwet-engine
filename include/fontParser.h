#pragma once

#ifndef WINDOW_SETTINGS
	#define WINDOW_SETTINGS
	#define WINDOW_WIDTH 800
	#define WINDOW_HEIGHT 600
#endif

#include<string>
#include<iostream>
#include<vector>
#include<sstream>
#include<fstream>
#include "gameObj.h"
#include "vecs.h"

/*
* This class is ment for adding custom font faces to your game engine, it uses the .fnt file format, and reads off of a .png text sprite.
* Line width is the width of a line given in pixels, that is converted so it fits the window coordinates.
* Since the text is being bound to a ObjectInfo structure it's x, y, z coordinates will affect it's posisioning as well as the shaders.
*/

struct CharInfo
{
	int id; //char id (have to find what the ids of chars are)
	int x; //location of start of char (topleft of the char)
	int y;
	int width; //width and height of the char
	int height;
	int xoffset; //how much to offset the char on both axis
	int yoffset;
	int xadvance; //how much to move forward to the next position to palce the character
	vecs::vec2 UV[4]; //UVs for the letter
};

class Font
{
	public:
		Font(std::string fontFilePath, std::string fontPicturePath, int* windowRes, float scale);

		~Font();

		void setLineWidth(int width);

		void setScale(float scale);

		void appendString(std::string text); //append a string to the class to be rendered

		void appendToObject(ObjectInfo* objectToAppendOnto); //add object to be appended to

		std::string getCurrentString();

	private:
		int maxLineWidth; //width of a line
		int imageResolution[2];
		int windowHeight;
		int windowWidth;
		int lineHeight;
		float scale;
		ObjectInfo* object;
		vecs::mesh fontMesh;
		std::string currentString;
		std::string fontFilePath;
		std::string fontPicturePath;
		std::map<int, CharInfo> charMap;

		void appendStringToObject(); //append the string to the object

		void convertToUV(); //converts the data to uvs on the texture

		void readFontFile(); //reads the .fnt file

		void calculateMesh(); //calculate the size of the mesh
};