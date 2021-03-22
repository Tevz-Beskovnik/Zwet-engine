#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<fstream>
#include<vector>
#include "viewport.h"
#include "vecCalc.h"
#include "vecs.h"

Viewport::Viewport(std::string vertDir, std::string fargDirC, std::string geometryDirC, std::vector<float>& vecC, GLenum type)
{
    vertexDir = vertDir;
    fragDir = fargDirC;
    startVec = vecC;
    drawType = type;
    geometryDir = geometryDirC;
    vecSize = vecC.size();
}

void convertMeshToArray(const vecs::mesh iMesh, std::vector<float>& oMesh)
{
    for (const auto& tri : iMesh.tris)
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

        //second vec3
        oMesh.push_back(tri.p[1].x);
        oMesh.push_back(tri.p[1].y);
        oMesh.push_back(tri.p[1].z);
        //colors for the triangle
        oMesh.push_back(tri.color.r);
        oMesh.push_back(tri.color.g);
        oMesh.push_back(tri.color.b);
        //add the normal

        //third vec3
        oMesh.push_back(tri.p[2].x);
        oMesh.push_back(tri.p[2].y);
        oMesh.push_back(tri.p[2].z);
        //colors for the triangle
        oMesh.push_back(tri.color.r);
        oMesh.push_back(tri.color.g);
        oMesh.push_back(tri.color.b);
        //add the normal
    }
};

unsigned int Viewport::initRender()
{
    float* positions = &startVec[0];

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_FRONT);

    unsigned int buffer;

    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, vecSize * sizeof(float), positions, drawType);

    unsigned int shader = createShader(vertexDir, fragDir, geometryDir);

    unsigned int coords = glGetAttribLocation(shader, "position");
    unsigned int color = glGetAttribLocation(shader, "iColor");

    glEnableVertexAttribArray(0);    
    glEnableVertexAttribArray(color);

    glVertexAttribPointer(
        coords,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        0
    );

    ptrdiff_t offsetColor = 3 * sizeof(float);

    glVertexAttribPointer(
        color,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*)offsetColor
    );

    return shader;
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

int Viewport::screenResolution()
{
    
}

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

unsigned int Viewport::createShader(const std::string vertexDir, const std::string fragDir, const std::string geometryDir)
{
    unsigned int program = glCreateProgram();

    std::string vertexShader;
    std::string fragShader;
    std::string geometryShader;

    readShader(vertexDir, vertexShader);
    readShader(fragDir, fragShader);
    readShader(geometryDir, geometryShader);

    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int gs = compileShader(GL_GEOMETRY_SHADER, geometryShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragShader);

    glAttachShader(program, vs);
    glAttachShader(program, gs);
    glAttachShader(program, fs);

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

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
};