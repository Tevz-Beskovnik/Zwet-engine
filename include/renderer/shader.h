#pragma once

#include <core.h>
#include <utils.h>
#include <log.h>

namespace ZWET
{
    struct ShaderData
    {
        std::string shaderDirectory;
	    unsigned int shaderType;
    };

    class Shader
    {
        public: 
            Shader(std::vector<ShaderData> settings);

            ~Shader();

            void bind();

            void unbind();

            void remove();

            unsigned int& getProgram() { return program; };

            static SharedPtr<Shader> create(std::vector<ShaderData> settings);

        private: 
            unsigned int program;
            unsigned int shaderLocation;
            std::string shader;
            std::vector<ShaderData> settings;

            bool readShader(std::string directory);

            bool compileShader(unsigned int type);

            bool createShader();
    };
}