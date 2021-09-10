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

            virtual ~Entity();

            static SharedPtr<Entity> create();
            
            virtual void create(tsl::hopscotch_map<int, SharedPtr<Entity>>& entityMap);

            virtual void stepStart(tsl::hopscotch_map<int, SharedPtr<Entity>>& entityMap);

            virtual void step(tsl::hopscotch_map<int, SharedPtr<Entity>>& entityMap);

            virtual void stepEnd(tsl::hopscotch_map<int, SharedPtr<Entity>>& entityMap);

            void newMesh(mesh newMesh);

            void setEntityData(entityData data);
            
        private:
            entityData data;
            SharedPtr<VertexBuffer> vertexBuffer;
            SharedPtr<FrameBuffer> frameBuffer;
            SharedPtr<Shader> shader;
            SharedPtr<Texture> texture;
            bool physicsEnabled;
            vec3 velocity;
            float weight;

            mesh entityMesh;
            std::vector<float> convretMesh;
    };
}