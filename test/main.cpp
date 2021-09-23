#ifdef __APPLE__
    #define PATH "/Users/tevz/documents/programing/Zwet-Engine/test/resources/"
#else
    #define PATH ""
#endif

/*
    ZWET_INFO\("[\w\s\W]{1,50}"\);\n

    regex to remove info
*/

#include <zwet.h>

using namespace ZWET;

using EntityMap = tsl::hopscotch_map<int, SharedPtr<Entity>>;

class CubeEntityCam : public Entity
{
    public:
        std::string classFamily = "cube";

        float entityYaw = 0.0f;
        float entityPitch = 0.0f;

        std::string getFamilyName()
        {
            return classFamily;
        }

        void createFun(EntityMap& entityMap, SharedPtr<Camera>& cam)
        {
            std::cout << "Yes hello this is the create function" << std::endl;
        }

        /*void step(EntityMap& entityMap, SharedPtr<Camera>& cam, double delta)
        {
            std::cout << delta << std::endl;

            float& yaw = cam->getYaw();
            float& pitch = cam->getPitch();
            float& forward = cam->getForward();
            float& sideways = cam->getSideways();
            vec3& pos = cam->getPosition();

            //std::cout << pos.x << " " << pos.y << " " << pos.z << std::endl;

            //movement mods for by how muh it should increase the movement speed
            const float movementMod = 0.08f;
            const float yawMod = 0.03f;

            //camera controls for yaw and pitch
            pitch += (-yawMod * keyBoard->isKeyHeld(GLFW_KEY_DOWN) + yawMod * keyBoard->isKeyHeld(GLFW_KEY_UP));

            //camera controls for movement
            pos.y += (movementMod * keyBoard->isKeyHeld(GLFW_KEY_SPACE)) + (-movementMod * keyBoard->isKeyHeld(GLFW_KEY_LEFT_SHIFT));
            forward = ((movementMod * keyBoard->isKeyHeld(GLFW_KEY_W)) + (-movementMod * keyBoard->isKeyHeld(GLFW_KEY_S)));
            sideways = ((-movementMod * keyBoard->isKeyHeld(GLFW_KEY_A)) + (movementMod * keyBoard->isKeyHeld(GLFW_KEY_D)));

            int yawLoc = glGetUniformLocation(shader->getProgram(), "objYaw");
            int pitchLoc = glGetUniformLocation(shader->getProgram(), "objPitch");

            mat4 objYaw = rotY(entityYaw);
            mat4 objPicth = rotX(entityPitch);

            glUniformMatrix4fv(yawLoc, 1, GL_FALSE, &objYaw.r[0][0]);
            glUniformMatrix4fv(pitchLoc, 1, GL_FALSE, &objPicth.r[0][0]);
        }*/
};

class CubeEntity : public Entity
{
    public:
        std::string classFamily = "cube1";

        std::string getFamilyName()
        {
            return classFamily;
        }

        void createFun(EntityMap& entityMap, SharedPtr<Camera>& cam)
        {
            std::cout << "Yes hello this is the create function of cube1" << std::endl;
        }
};

class Car : public Entity
{
    std::string familyName = "car";

    const float movementMod = 0.02f;
    const float yawMod = 0.03f;
    const float topSpeed = 0.5f;
    const float braking = 0.008f;

    float entityYaw = 0.0f;
    float entityPitch = 0.0f;

    float velocity = 0.0f;

    std::string getFamilyName()
    {
        return familyName;
    }

    void createFun(EntityMap& entityMap, SharedPtr<Camera>& cam)
    {
        float& yaw = cam->getYaw();
        yaw = 1.57079633;
    }

    void step(EntityMap& entityMap, SharedPtr<Camera>& cam, double delta)
    {
        float& yaw = cam->getYaw();
        float& pitch = cam->getPitch();
        float& forward = cam->getForward();
        float& sideways = cam->getSideways();
        vec3& pos = cam->getPosition();

        pos.y = 4.0f;

        pitch = -0.54079633;

        velocity += (velocity < topSpeed && velocity > -topSpeed) * ((movementMod * keyBoard->isKeyHeld(GLFW_KEY_W)) + (-movementMod * keyBoard->isKeyHeld(GLFW_KEY_S)));
        velocity += (velocity > 0.0f) * (-braking * (!keyBoard->isKeyHeld(GLFW_KEY_W) && !keyBoard->isKeyHeld(GLFW_KEY_S)));
        velocity += (velocity < 0.0f) * (braking * (!keyBoard->isKeyHeld(GLFW_KEY_W) && !keyBoard->isKeyHeld(GLFW_KEY_S)));
        if(velocity < -topSpeed)
            velocity = -topSpeed;
        else if(velocity > topSpeed)
            velocity = topSpeed;

        if(floor(abs(velocity * 100) < 1))
            velocity = 0;
            
        forward = velocity;

        std::cout << velocity << std::endl;

        yaw += velocity * 1.3 * (-yawMod * keyBoard->isKeyHeld(GLFW_KEY_D) + yawMod * keyBoard->isKeyHeld(GLFW_KEY_A));

        entityYaw = -yaw;

        int yawLoc = glGetUniformLocation(shader->getProgram(), "uObjYaw");
        int pitchLoc = glGetUniformLocation(shader->getProgram(), "uObjPitch");

        mat4 objYaw = rotY(entityYaw);
        mat4 objPicth = rotX(entityPitch);

        glUniformMatrix4fv(yawLoc, 1, GL_FALSE, &objYaw.r[0][0]);
        glUniformMatrix4fv(pitchLoc, 1, GL_FALSE, &objPicth.r[0][0]);
    }
};

int main()
{
    std::string path = PATH;
    
    Application testApp;
    
    testApp.setFpsCap(60);
    
    testApp.setWindowDims(2560, 1600);
    
    Scene scene(path + "scenes/sceneExample.json");
    
    SharedPtr<Camera> camera = Camera::create(0, 0, 0);
    
    camera->create3d(2560, 1600, 1000.0f, 0.1f, 90);

    scene.setCamera(camera);

    SharedPtr<Entity> ent1 = CreateShared<CubeEntityCam>();

    SharedPtr<Entity> ent2 = CreateShared<CubeEntity>();

    SharedPtr<Entity> ent3 = CreateShared<Car>();

    scene.registerEntity(ent1);

    scene.registerEntity(ent2);

    scene.registerEntity(ent3);

    testApp.setScene(scene);
    
    testApp.run();
}