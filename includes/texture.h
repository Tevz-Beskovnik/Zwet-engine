#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

class Texture
{
	public:
		Texture(std::string path);
		
		void DeleteTex();

		void bind();

		void unbind();

		bool definied();
	private:
		std::string filePath;
		unsigned int texture;
		unsigned char* textureBuffer;
		int width, height, BPP;
};