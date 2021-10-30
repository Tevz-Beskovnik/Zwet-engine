#pragma once

#include <core.h>
#include <structs.h>
#include <utils.h>
#include <vecCalc.h>

namespace ZWET 
{
    struct triangle
    {
        vec3 p[3];
        vec2 texUV[3];
        rgb color;
        vec3 normal;
    };

    struct mesh
    {
        std::vector<triangle> tris;
    };

    class Mesh
    {
        public:
            Mesh();

            ~Mesh();

            static std::vector<float> convertMesh(mesh inputMesh);

            static bool readMesh(mesh &inputMesh, std::string modelLocation, rgb color);

            static void applyStaticRotation(mesh& mesh, vec3 rotationVector, vec3 position);
    };
}