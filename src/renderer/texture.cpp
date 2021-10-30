#include <texture.h>

/*
glActiveTexture
activates the given texture unnit allows to bind multiple textures for single draw call
*/

namespace ZWET
{
	Texture::Texture(std::string path)
		: filePath(path), texture(0), textureBuffer(nullptr), width(0), height(0), BPP(0)
	{
		if (!path.empty())
		{
			stbi_set_flip_vertically_on_load(true);
			textureBuffer = stbi_load(filePath.c_str(), &width, &height, &BPP, 0);

			//generate texture
			glGenTextures(1, &texture);
			//bind the texture	
			glBindTexture(GL_TEXTURE_2D, texture);
			//add the texture parameters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureBuffer);

			glGenerateMipmap(GL_TEXTURE_2D);

			stbi_image_free(textureBuffer);
		}
	}

	void Texture::DeleteTex()
	{
		glDeleteTextures(1, &texture);
	}

	void Texture::bind()
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
	}

	void Texture::unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	bool Texture::definied()
	{
		return filePath.empty() == 1;
	}

	SharedPtr<Texture> Texture::create(std::string path)
	{
		return CreateShared<Texture>(path);
	}
}