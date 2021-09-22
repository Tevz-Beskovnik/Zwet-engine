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

        void step(EntityMap& entityMap, SharedPtr<Camera>& cam)
        {
            float& yaw = cam->getYaw();
            float& pitch = cam->getPitch();
            float& forward = cam->getForward();
            float& sideways = cam->getSideways();
            vec3& pos = cam->getPosition();

            /*movement mods for by how muh it should increase the movement speed*/
            const float movementMod = 0.08f;
            const float yawMod = 0.03f;

            //camera controls for yaw and pitch
            pitch += (-yawMod * keyBoard->isKeyHeld(GLFW_KEY_DOWN) + yawMod * keyBoard->isKeyHeld(GLFW_KEY_UP));
            yaw += (-yawMod * keyBoard->isKeyHeld(GLFW_KEY_RIGHT) + yawMod * keyBoard->isKeyHeld(GLFW_KEY_LEFT));

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
        }
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

int main()
{
    std::string path = PATH;

    ZWET_INFO("In main function");

    Application testApp;

    ZWET_INFO("Setting up window");

    testApp.setup();

    ZWET_INFO("Created application");

    testApp.setFpsCap(60);

    ZWET_INFO("Set fps cap");

    testApp.setWindowDims(1920, 1080);

    ZWET_INFO("Set window dims");

    Scene scene(path + "scenes/sceneExample.json");

    ZWET_INFO("Created scene");

    SharedPtr<Camera> camera = Camera::create(0, 0, 0);

    ZWET_INFO("Created camera");

    camera->create3d(1920, 1080, 1000.0f, 0.1f, 70);

    scene.setCamera(camera);

    SharedPtr<Entity> ent1 = CreateShared<CubeEntityCam>();

    SharedPtr<Entity> ent2 = CreateShared<CubeEntity>();

    scene.registerEntity(ent1);

    scene.registerEntity(ent2);

    ZWET_INFO("Registered entities");

    testApp.setScene(scene);

    ZWET_INFO("Set scene");

    ZWET_INFO("Started loop");

    testApp.run();
}