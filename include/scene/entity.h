#pragma once

#include <core.h>
#include <utils.h>
#include <log.h>
#include <structs.h>
#include <mesh.h>
#include <frameBuffer.h>
#include <vertexBuffer.h>
#include <shader.h>
#include <texture.h>

namespace ZWET
{
    struct entityData
    {
        std::string name;
        //object position and rotation
        vec3 position;
        vec3 staticRotation;
        vec3 dynamicRotation;

        //color
        rgb color = { 1.0f, 1.0f, 1.0f };

        //rendering stuff
        std::string texturePath;
        std::string modelLocation;
        std::vector<ShaderData> shaderData;
        FrameBufferSettings frameBufferSettings;

        //physics
        bool physicsObject = false;
        float weight = 1.0f;
        vec3 velocity = { 0.0f, 0.0f, 0.0f };
    };

    class Entity
    {
        public:
            vec3 position;
            vec3 dynamicRotation;
            int entityId;
            std::string family;

            Entity(entityData data);

            ~Entity();

            static SharedPtr<Entity> create(entityData data);

            void setStepFunction(std::function<void(tsl::hopscotch_map<int, SharedPtr<Entity>>&)> step);

            void stepFunction(tsl::hopscotch_map<int, SharedPtr<Entity>>& entityMap);

            void setCreateFunction(std::function<void(tsl::hopscotch_map<int, SharedPtr<Entity>>&)> create);

            void createFunction(tsl::hopscotch_map<int, SharedPtr<Entity>>& entityMap);

            void newMesh(mesh newMesh);

            void setEntityData(entityData data);
            
        private:
            entityData data;
            std::function<void(tsl::hopscotch_map<int, SharedPtr<Entity>>&)> stepFunc;
            std::function<void(tsl::hopscotch_map<int, SharedPtr<Entity>>& entityMap)> createFunc;
            SharedPtr<VertexBuffer> vertexBuffer;
            SharedPtr<FrameBuffer> frameBuffer;
            SharedPtr<Shader> shader;
            SharedPtr<Texture> texture;

            mesh entityMesh;
            std::vector<float> convretMesh;
    };
}