#include <scene.h>

namespace ZWET
{
    Scene::Scene(std::string scenePath)
        :scenePath(scenePath)
    {

    }

    Scene::~Scene()
    {

    }

    UniquePtr<Scene> Scene::create(std::string scenePath)
    {
        return CreateUnique<Scene>(scenePath);
    }

    void Scene::sceneCreate()
    {

    }

    void Scene::sceneStep()
    {

    }

    void Scene::addEntity(SharedPtr<Entity>)
    {

    }

    void Scene::removeEntity(SharedPtr<Entity>)
    {

    }

    EntityMap& Scene::getEntities()
    {
        return entities;
    }

    void Scene::serializeScene()
    {
        sceneToSerialise = padded_string::load(scenePath);
        doc = parser.iterate(sceneToSerialise);
        auto sceneArray = doc.get_array();

        for(ondemand::object entity : sceneArray)
        {
            entityData newEntity;

            newEntity.name = std::string_view(entity["name"]);

            newEntity.position.x = (float)entity["position"]["x"].get_double();
            newEntity.position.y = (float)entity["position"]["y"].get_double();
            newEntity.position.z = (float)entity["position"]["z"].get_double();

            newEntity.staticRotation.x = (float)entity["static_rotation"]["x"].get_double();
            newEntity.staticRotation.y = (float)entity["static_rotation"]["y"].get_double();
            newEntity.staticRotation.z = (float)entity["static_rotation"]["z"].get_double();
            
            newEntity.dynamicRotation.x = (float)entity["dynamic_rotation"]["x"].get_double();
            newEntity.dynamicRotation.y = (float)entity["dynamic_rotation"]["y"].get_double();
            newEntity.dynamicRotation.z = (float)entity["dynamic_rotation"]["z"].get_double();

            newEntity.color.r = (float)entity["rgb"]["r"].get_double();
            newEntity.color.g = (float)entity["rgb"]["g"].get_double();
            newEntity.color.b = (float)entity["rgb"]["b"].get_double();

            newEntity.texturePath = std::string_view(entity["texture_path"]);
            newEntity.modelLocation = std::string_view(entity["model_location"]);

            std::string vertexShaderLoc = "";
            vertexShaderLoc += std::string_view(entity["vertex_shader"]);
            newEntity.shaderData.push_back({
                vertexShaderLoc,
                GL_VERTEX_SHADER
            });

            std::string fragShaderLoc = "";
            fragShaderLoc += std::string_view(entity["fragment_shader"]);
            newEntity.shaderData.push_back({
                fragShaderLoc,
                GL_FRAGMENT_SHADER
            });

            newEntity.physicsObject = entity["physics"].get_bool();

            newEntity.weight += (float)entity["weight"].get_double();

            newEntity.velocity.x = (float)entity["velocity"]["x"].get_double();
            newEntity.velocity.y = (float)entity["velocity"]["y"].get_double();
            newEntity.velocity.z = (float)entity["velocity"]["z"].get_double();

            addToEntities(newEntity);
        }
    }

    void Scene::addToEntities(entityData entity)
    {
        addToEntityFamilyMap(entity);

        SharedPtr<Entity> entityObject = CreateShared<Entity>(entityFamilies[entity.name]);
        entityObject->setEntityData(entity);
        entities.insert({entityCount, entityObject});

        entityCount++;
    } 
            
    bool Scene::addToEntityFamilyMap(entityData entity)
    {
        if(entityFamilies.find(entity.name) != entityFamilies.end())
            return false;

        entityFamilies.insert({
            entity.name,
            CreateShared<Entity>(entity)
        });

        return true;
    }

    std::vector<int> Scene::getEntityRelations(std::string familyName)
    {
        if(entityRelations.find(familyName) != entityRelations.end())
            return entityRelations[familyName]; 
        else
            return {};
    }

    bool Scene::applyCreateToEntity(EntityFunction createFunc)
    {
        
    }

    bool Scene::applyStepToEntity(EntityFunction stepFunc)
    {

    }
}