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
#include <drawer.h>
#include <keyInput.h>
#include <camera.h>

namespace ZWET
{
    class Entity;

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

    using EntityMap = tsl::hopscotch_map<int, Entity>;

    class Entity
    {
        public:
            vec3 position;
            vec3 dynamicRotation;
            int entityId;
            std::string family;
            SharedPtr<VertexBuffer> vertexBuffer;
            SharedPtr<FrameBuffer> frameBuffer;
            SharedPtr<Shader> shader;
            SharedPtr<Texture> texture;
            SharedPtr<Drawer> drawer;

            virtual ~Entity() {};

            virtual std::string getFamilyName() { return family; };
            
            virtual void createFun(EntityMap& entityMap, SharedPtr<Camera>& cam) {};

            virtual void stepStart(EntityMap& entityMap, SharedPtr<Camera>& cam) {};

            virtual void step(EntityMap& entityMap, SharedPtr<Camera>& cam) {};

            virtual void stepEnd(EntityMap& entityMap, SharedPtr<Camera>& cam) {};

            void newMesh(mesh newMesh);

            void setEntityData(entityData data);

            void setKeyInput(SharedPtr<KeyboardInput> keyInput);
            
        protected:
            SharedPtr<KeyboardInput> keyBoard;

            entityData data;
            bool physicsEnabled;
            vec3 velocity;
            float weight;

            mesh entityMesh;
            std::vector<float> convretMesh;
    };
}