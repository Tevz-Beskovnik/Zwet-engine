#ifdef __APPLE__
    #define PATH "/Users/tevz/documents/programing/Zwet-Engine/test/resources/"
#else
    #define PATH ""
#endif

#include <zwet.h>

using namespace ZWET;

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

        void createFun(tsl::hopscotch_map<int, Entity>& entityMap, SharedPtr<Camera>& cam)
        {
            std::cout << "Yes hello this is the create function" << std::endl;
        }

        void step(tsl::hopscotch_map<int, Entity>& entityMap, SharedPtr<Camera>& cam)
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

        void stepStart(tsl::hopscotch_map<int, Entity>& entityMap, SharedPtr<Camera>& cam)
        {

        }

        void stepEnd(tsl::hopscotch_map<int, Entity>& entityMap, SharedPtr<Camera>& cam)
        {

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

        void createFun(tsl::hopscotch_map<int, Entity>& entityMap, SharedPtr<Camera>& cam)
        {
            std::cout << "Yes hello this is the create function of cube1" << std::endl;
        }

        void stepStart(tsl::hopscotch_map<int, Entity>& entityMap, SharedPtr<Camera>& cam)
        {

        }

        void stepEnd(tsl::hopscotch_map<int, Entity>& entityMap, SharedPtr<Camera>& cam)
        {

        }
};

int main()
{
    std::string path = PATH;

    Application testApp;

    testApp.setFpsCap(60);

    testApp.setWindowDims(1920, 1080);

    Scene scene(path + "scenes/sceneExample.json");

    SharedPtr<Camera> camera = Camera::create(0, 0, 0);

    camera->create3d(1920, 1080, 1000.0f, 0.1f, 70);

    CubeEntityCam ent1;

    CubeEntity ent2;

    scene.registerEntity(ent1);

    scene.registerEntity(ent2);

    testApp.setScene(scene);

    testApp.run();
}