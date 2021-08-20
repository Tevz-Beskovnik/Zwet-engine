#pragma once

#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include "vecs.h"

#ifndef VP_DEFAULFT_RENDER_BUFF
	#define VP_DEFAULFT_RENDER_BUFF 0
#endif

#ifndef VP_CUSTOM_RENDER_BUFF
	#define VP_CUSTOM_RENDER_BUFF 1
#endif

void convertMeshToArray(const vecs::mesh, std::vector<float>&);

typedef struct
{
	std::string shader;
	unsigned int shaderType;
} ShaderInfo;

class Viewport {
	public:
		std::vector<float> startVec;
		GLenum drawType;
		int vecSize;

		Viewport(std::vector<float>&, GLenum);

		// PRE-RENDER

		void genBuffer(unsigned int*);

		void bindBufferData(unsigned int&);

		unsigned int createShader(std::vector<ShaderInfo>);

		unsigned int setupFramebuffer(int frameBufferWidth, int frameBufferHeight);

		unsigned int getFrameBufferTexture();

		void bindFrameBuffer(unsigned int);

		// RENDER

		void bindAttributes(unsigned int&, unsigned int&);

		void bindAttribute(unsigned int& program, unsigned int& buffer, std::string attribName, int size, GLenum type, GLenum normalise, int sizeInBytes, ptrdiff_t offset);

		void render(GLenum mode, int first, int vertCount);

		// POST-RENDER

		void unbindFrameBuffer();

	private:
		//things to do with frame buffer and frame buffer texture
		unsigned int frameBuffer;
		unsigned int frameBufferTex;
		unsigned int renderBufferObject;
		int frameBufferWidth;
		int frameBufferHeight;

		//Frame buffer stuff
		void genFrameBuffer(int textureWidth, int textureHeight);

		void genFrameBufferTex();

		void genRednderBuffer();

		void attachToRenderBuffer();
		//Frame buffer stuff

		void readShader(std::string, std::string&);

		unsigned int compileShader(unsigned int, const std::string&);
};