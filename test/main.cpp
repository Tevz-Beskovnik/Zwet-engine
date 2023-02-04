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

/*class Room : public Entity
{
    public:
        std::string classFamily = "room";

        float entityYaw = 0.0f;
        float entityPitch = 0.0f;

        std::string getFamilyName()
        {
            return classFamily;
        }

        void createFun(EntityMap& entityMap, SharedPtr<Camera>& cam, Scene& scene)
        {
            std::cout << "Yes hello this is the create function" << std::endl;
        }

        void step(EntityMap& entityMap, SharedPtr<Camera>& cam, Scene& scene, double delta)
        {
            float& yaw = cam->getYaw();
            float& pitch = cam->getPitch();
            float& forward = cam->getForward();
            float& sideways = cam->getSideways();
            vec3& pos = cam->getPosition();

            //movement mods for by how muh it should increase the movement speed
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
};*/


class Plant : public Entity
{
    public:
        std::string classFamily = "room";

        const float right_angle_rad = 1.57079633f;
        const float rotation_incr = 0.02f;
        const float max_forward = 5.5f;

        std::string getFamilyName()
        {
            return classFamily;
        }

        void createFun(EntityMap& entityMap, SharedPtr<Camera>& cam, Scene& scene)
        {
            vec3& pos = cam->getPosition();
            pos.y = 3.0f;
            pos.z = -8.0f;
            scene.dynamicSceneRotation = { 0.0f, 0.0f, 0.0f };
            std::cout << "Yes hello this is the create function" << std::endl;
        }

        void step(EntityMap& entityMap, SharedPtr<Camera>& cam, Scene& scene, double delta)
        {
            float& forward = cam->getForward();

            if(/*scene.dynamicSceneRotation.x > -right_angle_rad && */!keyBoard->isKeyHeld(GLFW_KEY_S))
                scene.dynamicSceneRotation.x -= rotation_incr * keyBoard->isKeyHeld(GLFW_KEY_W);

            if(/*scene.dynamicSceneRotation.x < 0 && */!keyBoard->isKeyHeld(GLFW_KEY_W))
                scene.dynamicSceneRotation.x += rotation_incr * keyBoard->isKeyHeld(GLFW_KEY_S);

            if(/*scene.dynamicSceneRotation.y < right_angle_rad && */!keyBoard->isKeyHeld(GLFW_KEY_A))
                scene.dynamicSceneRotation.y += rotation_incr * keyBoard->isKeyHeld(GLFW_KEY_D);

            if(/*scene.dynamicSceneRotation.y > 0 && */!keyBoard->isKeyHeld(GLFW_KEY_D))
                scene.dynamicSceneRotation.y -= rotation_incr * keyBoard->isKeyHeld(GLFW_KEY_A);

            forward = (-rotation_incr*keyBoard->isKeyHeld(GLFW_KEY_DOWN) + rotation_incr*keyBoard->isKeyHeld(GLFW_KEY_UP));
        }
};

int main()
{
    std::string path = PATH;

    ZWET_INFO("In main function");

    Application testApp;

    ZWET_INFO("Created application");

    testApp.setFpsCap(60);

    ZWET_INFO("Set fps cap");

    testApp.setWindowDims(2560, 1600);

    ZWET_INFO("Set window dims");

    Scene scene(path + "scenes/sceneDemo3.json");

    Font arial(path + "fonts/arial.fnt", path + "fonts/arial.jpg", 0, 0, 0.01f);

    ZWET_INFO("Created scene");

    SharedPtr<Camera> camera = Camera::create(0, 0, 0);

    ZWET_INFO("Created camera");

    camera->create3d(2560, 1600, 1000.0f, 0.1f, 90);

    scene.setCamera(camera);

    SharedPtr<Entity> ent1 = CreateShared<Plant>();

    scene.registerEntity(ent1);

    ZWET_INFO("Registered entities");

    testApp.setScene(scene);

    testApp.setBackgroundColor({0.2588f, 0.5294f, 0.9607f});
    //testApp.setBackgroundColor({1.0f, 1.0f, 1.0f});

    ZWET_INFO("Set scene");

    ZWET_INFO("Started loop");

    testApp.run();
}