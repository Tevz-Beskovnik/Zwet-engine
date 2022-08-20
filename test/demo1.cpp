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

    void createFun(EntityMap& entityMap, SharedPtr<Camera>& cam, Scene& scene)
    {
        float& yaw = cam->getYaw();
        yaw = 1.57079633;
    }

    void step(EntityMap& entityMap, SharedPtr<Camera>& cam, Scene& scene, double delta)
    {
        float& yaw = cam->getYaw();
        float& pitch = cam->getPitch();
        float& forward = cam->getForward();
        float& sideways = cam->getSideways();
        vec3& pos = cam->getPosition();
        scene.dynamicSceneRotation.x = 0;
        scene.dynamicSceneRotation.y = 0;
        scene.dynamicSceneRotation.z = 0;

        pos.y = 2.0f;

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

    ZWET_INFO("In main function");

    Application testApp;

    ZWET_INFO("Created application");

    testApp.setFpsCap(60);

    ZWET_INFO("Set fps cap");

    testApp.setWindowDims(2560, 1600);

    ZWET_INFO("Set window dims");

    Scene scene(path + "scenes/sceneDemo1.json");

    Font arial(path + "fonts/arial.fnt", path + "fonts/arial.jpg", 0, 0, 0.01f);

    ZWET_INFO("Created scene");

    SharedPtr<Camera> camera = Camera::create(0, 0, 0);

    ZWET_INFO("Created camera");

    camera->create3d(2560, 1600, 1000.0f, 0.1f, 90);

    scene.setCamera(camera);

    SharedPtr<Entity> ent1 = CreateShared<Car>();

    scene.registerEntity(ent1);

    ZWET_INFO("Registered entities");

    testApp.setScene(scene);

    testApp.setBackgroundColor({0.2588f, 0.5294f, 0.9607f});
    //testApp.setBackgroundColor({0.0f, 0.0f, 0.0f});

    ZWET_INFO("Set scene");

    ZWET_INFO("Started loop");

    testApp.run();
}