#include<string>
#include<fstream>
#include<vector>
#include"vecs.h"

//definitions for all hte diffrent file extentions
#ifndef OBJ
    #define OBJ 0
#endif

#ifndef DAE
    #define DAE 1
#endif

#ifndef PLY
    #define PLY 2
#endif

#ifndef STF
    #define STF 3
#endif

#ifndef FBX
    #define FBX 4
#endif

class Model
{
    public:
        Model(std::string& modelDirectiry);

        void changeModel(std::string newModelDirectory);

        vecs::mesh getMesh();

    private:
        std::string& modelLocation;
        vecs::mesh modelMesh;

        bool makeMesh();
};