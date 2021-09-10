#include <entity.h>

namespace ZWET 
{
    SharedPtr<Entity> Entity::create()
    {
        return CreateShared<Entity>();
    }

    void Entity::newMesh(mesh newMesh)
    {
        entityMesh = newMesh;

        convretMesh = Mesh::convertMesh(entityMesh);

        Mesh::applyStaticRotation(entityMesh, data.staticRotation, position);

        vertexBuffer.reset();

        vertexBuffer = CreateShared<VertexBuffer>(convretMesh);
    }

    void Entity::setEntityData(entityData data)
    {
        position = data.position;
        dynamicRotation = data.dynamicRotation;
        texture = Texture::create(data.texturePath);
        shader = Shader::create(data.shaderData);
        frameBuffer = FrameBuffer::create(&data.frameBufferSettings);
        physicsEnabled = data.physicsObject;
        velocity = data.velocity;
        weight = data.weight;

        if(!Mesh::readMesh(entityMesh, data.modelLocation, data.color))
        {
            ZWET_ERROR("THE FILE COULD NOT BE READ.");
            return;
        }

        Mesh::applyStaticRotation(entityMesh, data.staticRotation, data.position);

        convretMesh = Mesh::convertMesh(entityMesh);

        vertexBuffer = VertexBuffer::create(1, &convretMesh);
    }
}
