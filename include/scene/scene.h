#pragma once

#include <core.h>
#include <utils.h>
#include <log.h>
#include <entity.h>

namespace ZWET
{
    using EntityMap = tsl::hopscotch_map<int, SharedPtr<Entity>>;
    using EntityFamilyMap = tsl::hopscotch_map<std::string, SharedPtr<Entity>>;
    using FamilyRelationsMap = tsl::hopscotch_map<std::string, std::vector<int>>;
    using namespace simdjson;

    class Scene
    {
        public:
            Scene(std::string scenePath);

            ~Scene();

            static UniquePtr<Scene> create(std::string scenePath);

            void sceneCreateFunc();

            void sceneStepFunc();

            void registerEntity(SharedPtr<Entity> entity);

            void removeEntity(int entityId);

            std::vector<int> getEntityRelations(std::string familyName);

            EntityMap& getEntities();
        private:
            int entityCount = 0;
            std::string scenePath;
            EntityFamilyMap entityFamilies;
            EntityMap entities;
            FamilyRelationsMap entityRelations;
            ondemand::parser parser;
            padded_string sceneToSerialise;
            ondemand::document doc;

            void serializeScene();

            void addToEntities(entityData entity);

            void addRelation(std::string family, int location);

            bool addToEntityFamilyMap(SharedPtr<Entity> entity);
    };
}