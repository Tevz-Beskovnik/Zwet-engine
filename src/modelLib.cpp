#include"modelLib.h"

Model::Model(std::string& modelDir)
    :modelLocation(modelDir)
{
    makeMesh();
}

void Model::changeModel(std::string newModelDir)
{
    modelLocation = newModelDir;
    makeMesh();
}

vecs::mesh Model::getMesh()
{
    return modelMesh;
}

bool Model::makeMesh()
{
    ;
}