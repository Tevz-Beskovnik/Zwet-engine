#include <entity.h>

namespace ZWET 
{
    void Entity::newMesh(mesh newMesh)
    {
        entityMesh = newMesh;

        convretMesh = Mesh::convertMesh(entityMesh);

        Mesh::applyStaticRotation(entityMesh, data.staticRotation, position);

        vertexBuffer.reset();

        vertexBuffer = CreateShared<VertexBuffer>(1, &convretMesh);
    }

    void Entity::setEntityData(entityData data)
    {
        position = data.position;
        dynamicRotation = data.dynamicRotation;
        texture = Texture::create(data.texturePath);
        shader = Shader::create(data.shaderData);
        //frameBuffer = FrameBuffer::create(&data.frameBufferSettings);
        std::cout << data.shaderData[0].shaderDirectory << std::endl;
        std::cout << data.shaderData[1].shaderDirectory << std::endl;
        physicsEnabled = data.physicsObject;
        velocity = data.velocity;
        weight = data.weight;

        if(!Mesh::readMesh(entityMesh, data.modelLocation, data.color))
        {
            ZWET_ERROR("THE FILE " + data.modelLocation + " COULD NOT BE READ.");
            return;
        }

        Mesh::applyStaticRotation(entityMesh, data.staticRotation, data.position);

        convretMesh = Mesh::convertMesh(entityMesh);

        vertexBuffer = VertexBuffer::create(1, &convretMesh);

        std::cout << "Poly count: " << vertexBuffer->getPolyCount() << std::endl;

        drawer = Drawer::create(GL_TRIANGLES, 0, vertexBuffer->getPolyCount());
    }

    void Entity::setKeyInput(SharedPtr<KeyboardInput> keyInput)
    {
        ZWET_INFO("In set key input func");
        keyBoard = keyInput;
    }
}
