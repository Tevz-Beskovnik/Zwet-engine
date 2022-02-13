#pragma once

#ifndef WORLD_TYPE
    #define WORLD_TYPE
    #define WORLD_3D
#endif

#include <core.h>
#include <utils.h>
#include <log.h>
#include <entity.h>
#include <vecCalc.h>
#include <camera.h>
#include <keyInput.h>

namespace ZWET
{
    using EntityMap = tsl::hopscotch_map<int, SharedPtr<Entity>>;
    using EntityFamilyMap = tsl::hopscotch_map<std::string, SharedPtr<Entity>>;
    using FamilyRelationsMap = tsl::hopscotch_map<std::string, std::vector<int>>;
    using namespace simdjson;

    class Scene
    {
        public:
            mat4 world;
            mat4 inverseWorld;
            vec3 dynamicSceneRotation;

            Scene(std::string scenePath);

            ~Scene();

            static UniquePtr<Scene> create(std::string scenePath);

            void sceneCreateFunc();

            void sceneStepFunc();

            void setCamera(SharedPtr<Camera> camera);

            void registerEntity(SharedPtr<Entity> entity);

            void removeEntity(int entityId);

            void setKeyInputSource(GLFWwindow* window);

            void serialize();

            SharedPtr<Camera> getCamera();

            std::vector<int> getEntityRelations(std::string familyName);

            EntityMap& getEntities();

        private:
            //keyboard input
            SharedPtr<KeyboardInput> keyBoard;

            //camera stuff
            SharedPtr<Camera> camera;

            //entity relations
            int entityCount = 0;
            std::string scenePath;
            EntityFamilyMap entityFamilies;
            EntityMap entities;
            FamilyRelationsMap entityRelations;

            //document parsing
            ondemand::parser parser;
            padded_string sceneToSerialise;
            ondemand::document doc;

            void serializeScene();

            void addToEntities(entityData entity);

            void addRelation(std::string family, int location);

            bool addToEntityFamilyMap(SharedPtr<Entity> entity);
    };
}