#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<fstream>
#include<vector>
#include "viewport.h"
#include "vecCalc.h"
#include "vecs.h"

Viewport::Viewport(std::vector<float>& vecC, GLenum type)
    :frameBuffer(0)
{
    startVec = vecC;
    drawType = type;
    vecSize = vecC.size();
}

void convertMeshToArray(const vecs::mesh iMesh, std::vector<float>& oMesh)
{
    for (const vecs::triangle& tri : iMesh.tris)
    {
        //fist vec3
        oMesh.push_back(tri.p[0].x);
        oMesh.push_back(tri.p[0].y);
        oMesh.push_back(tri.p[0].z);
        //colors for the triangle
        oMesh.push_back(tri.color.r);
        oMesh.push_back(tri.color.g);
        oMesh.push_back(tri.color.b);
        //add the normal
        oMesh.push_back(tri.normal.x);
        oMesh.push_back(tri.normal.y);
        oMesh.push_back(tri.normal.z);
        //uvs
        oMesh.push_back(tri.texUv[0].x);
        oMesh.push_back(tri.texUv[0].y);

        //second vec3
        oMesh.push_back(tri.p[1].x);
        oMesh.push_back(tri.p[1].y);
        oMesh.push_back(tri.p[1].z);
        //colors for the triangle
        oMesh.push_back(tri.color.r);
        oMesh.push_back(tri.color.g);
        oMesh.push_back(tri.color.b);
        //add the normal
        oMesh.push_back(tri.normal.x);
        oMesh.push_back(tri.normal.y);
        oMesh.push_back(tri.normal.z);
        //uvs
        oMesh.push_back(tri.texUv[1].x);
        oMesh.push_back(tri.texUv[1].y);

        //third vec3
        oMesh.push_back(tri.p[2].x);
        oMesh.push_back(tri.p[2].y);
        oMesh.push_back(tri.p[2].z);
        //colors for the triangle
        oMesh.push_back(tri.color.r);
        oMesh.push_back(tri.color.g);
        oMesh.push_back(tri.color.b);
        //add the normal
        oMesh.push_back(tri.normal.x);
        oMesh.push_back(tri.normal.y);
        oMesh.push_back(tri.normal.z);
        //uvs
        oMesh.push_back(tri.texUv[2].x);
        oMesh.push_back(tri.texUv[2].y);
    }
};

void Viewport::genBuffer(unsigned int* buffer)
{
    glGenBuffers(1, buffer);
}

void Viewport::bindBufferData(unsigned int& buffer)
{
    float* positions = startVec.data();

    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, vecSize * sizeof(float), positions, drawType);
}

void Viewport::bindAttributes(unsigned int& program, unsigned int& buffer)
{
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    unsigned int coords = glGetAttribLocation(program, "position");
    unsigned int color = glGetAttribLocation(program, "iColor");
    unsigned int normal = glGetAttribLocation(program, "iNormal");
    unsigned int UV = glGetAttribLocation(program, "iUV");

    glEnableVertexAttribArray(coords);
    glEnableVertexAttribArray(color);
    glEnableVertexAttribArray(normal);
    glEnableVertexAttribArray(UV);

    glVertexAttribPointer(
        coords,
        3,
        GL_FLOAT,
        GL_FALSE,
        11 * sizeof(float),
        0
    );

    ptrdiff_t offsetColor = 3 * sizeof(float);

    glVertexAttribPointer(
        color,
        3,
        GL_FLOAT,
        GL_FALSE,
        11 * sizeof(float),
        (void*)offsetColor
    );

    ptrdiff_t offsetNormal = 6 * sizeof(float);

    glVertexAttribPointer(
        normal,
        3,
        GL_FLOAT,
        GL_FALSE,
        11 * sizeof(float),
        (void*)offsetNormal
    );

    ptrdiff_t offsetUV = 9 * sizeof(float);

    glVertexAttribPointer(
        UV,
        2,
        GL_FLOAT,
        GL_FALSE,
        11 * sizeof(float),
        (void*)offsetUV
    );
}

void Viewport::readShader(std::string path, std::string& shader)
{
    std::string line;
    std::ifstream shaderFile(path);

    if (shaderFile.is_open())
    {
        while (std::getline(shaderFile, line))
        {
            shader += line + "\n";
        }
    }
};

unsigned int Viewport::compileShader(unsigned int type, const std::string& shader)
{
    unsigned int id = glCreateShader(type);
    const char* src = shader.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

        char* message = (char*)malloc(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);

        std::cout << "Shader failed to compile" << (type == GL_VERTEX_SHADER ? "vertex: " : "fragment: ") << std::endl;
        std::cout << message << std::endl;

        glDeleteShader(id);

        return 0;
    }

    return id;
};

unsigned int Viewport::createShader(std::vector<ShaderInfo> shaders)
{
    unsigned int program = glCreateProgram();

    std::vector<unsigned int> delShader;

    for (const ShaderInfo& shader : shaders) 
    {
        std::string shaderSrc;

        readShader(shader.shader, shaderSrc);

        unsigned int sh = compileShader(shader.shaderType, shaderSrc);
        glAttachShader(program, sh);
        delShader.push_back(sh);
    }

    glLinkProgram(program);
    glValidateProgram(program);

    int result;
    glGetProgramiv(program, GL_VALIDATE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

        char* message = (char*)malloc(length * sizeof(char));
        glGetProgramInfoLog(program, length, &length, message);

        std::cout << "Program failed to validate:" << std::endl;
        std::cout << message << std::endl;

        return 0;
    }

    for (const auto& delSh : delShader)
    {
        glDeleteShader(delSh);
    }

    return program;
};

unsigned int Viewport::setupFramebuffer(int frameBufferWidth, int frameBufferHeight)
{
    genFrameBuffer(frameBufferWidth, frameBufferHeight);
    genFrameBufferTex();
    genRednderBuffer();
    attachToRenderBuffer();

    return frameBuffer;
}

void Viewport::bindFrameBuffer(unsigned int frameBuffer)
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBuffer);
}

void Viewport::genFrameBuffer(int textureWidth, int textureHeight)
{
    frameBufferWidth = textureWidth;
    frameBufferHeight = textureHeight;
    glGenFramebuffers(1, &frameBuffer);
}
	
void Viewport::genFrameBufferTex()
{
    glGenTextures(1, &frameBufferTex);
    glBindTexture(GL_TEXTURE_2D, frameBufferTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frameBufferWidth, frameBufferHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
	
void Viewport::genRednderBuffer()
{
    glGenRenderbuffers(1, &renderBufferObject);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBufferObject);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, frameBufferWidth, frameBufferHeight);
}
	
void Viewport::attachToRenderBuffer()
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frameBufferTex, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBufferObject);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
}

void Viewport::bindAttribute(unsigned int& program, unsigned int& buffer, std::string nameOfAttribute, int size, GLenum type, GLenum normalise, int totalSizeInBytes, ptrdiff_t offset)
{
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    unsigned int attribute = glGetAttribLocation(program, nameOfAttribute.c_str());

    glEnableVertexAttribArray(attribute);

    glVertexAttribPointer(
        attribute,
        size,
        type,
        normalise,
        totalSizeInBytes,
        (void*)offset
    );
}

void Viewport::render(GLenum mode, int first, int vertCount)
{
    glDrawArrays(mode, first, vertCount);
}

void Viewport::unbindFrameBuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

unsigned int Viewport::getFrameBufferTexture()
{
    return frameBufferTex;
}