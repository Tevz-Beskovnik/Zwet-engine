#include <entity.h>

namespace ZWET 
{
    void Entity::setMesh(mesh prMesh)
    {
        entityMesh = prMesh;

        presetMesh = true;
    }

    void Entity::newMesh(mesh newMesh)
    {
        entityMesh = newMesh;

        std::cout << "Static rot: " << data.staticRotation.y << std::endl;

        Mesh::applyStaticRotation(entityMesh, data.staticRotation, position);

        convretMesh = Mesh::convertMesh(entityMesh);

        vertexBuffer->setData(&convretMesh);

        drawer->setPolyCount(vertexBuffer->getPolyCount());
    }

    void Entity::setEntityData(entityData data)
    {
        std::cout << data.position.x << " " << data.position.y << " " << data.position.z << std::endl; 
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

        if(presetMesh == false)
            if(!Mesh::readMesh(entityMesh, data.modelLocation, data.color))
            {
                ZWET_ERROR("THE FILE " + data.modelLocation + " COULD NOT BE READ.");
                return;
            }

        std::cout << "Static rot: " << data.staticRotation.y << std::endl;

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
