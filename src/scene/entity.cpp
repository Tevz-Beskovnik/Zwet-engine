#include <entity.h>

namespace ZWET 
{
    Entity::Entity(entityData data)
        :position(data.position), 
         dynamicRotation(data.dynamicRotation),
         family(data.name),
         texture(Texture::create(data.texturePath)),
         shader(Shader::create(data.shaderData)),
         frameBuffer(FrameBuffer::create(&data.frameBufferSettings))
    {
        if(!Mesh::readMesh(entityMesh, data.modelLocation, data.color))
        {
            ZWET_ERROR("THE FILE COULD NOT BE READ.");
            return;
        }

        Mesh::applyStaticRotation(entityMesh, data.staticRotation, data.position);

        convretMesh = Mesh::convertMesh(entityMesh);

        vertexBuffer = VertexBuffer::create(1, &convretMesh);
    }

    Entity::~Entity()
    {
        ;
    }

    SharedPtr<Entity> Entity::create(entityData data)
    {
        return CreateShared<Entity>(data);
    }

    void Entity::setStepFunction(std::function<void(tsl::hopscotch_map<int, SharedPtr<Entity>>&)> step)
    {
        stepFunc = step;
    }

    void Entity::stepFunction(tsl::hopscotch_map<int, SharedPtr<Entity>>& entityMap)
    {
        stepFunc(entityMap);
    }

    void Entity::setCreateFunction(std::function<void(tsl::hopscotch_map<int, SharedPtr<Entity>>&)> create)
    {
        createFunc = create;
    }

    void Entity::createFunction(tsl::hopscotch_map<int, SharedPtr<Entity>>& entityMap)
    {
        createFunc(entityMap);
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
    }
}
