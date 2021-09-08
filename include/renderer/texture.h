#pragma once

#include <core.h>
#include <utils.h>

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#endif

namespace ZWET
{
	class Texture
	{
		public:
			Texture(std::string path);
			
			void DeleteTex();
	
			void bind();
	
			void unbind();
	
			bool definied();
	
			static SharedPtr<Texture> create(std::string path);
		private:
			std::string filePath;
			unsigned int texture;
			unsigned char* textureBuffer;
			int width, height, BPP;
	};
}