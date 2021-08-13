#ifndef PI
    #define PI 3.14159265358979323846
#endif // PI

#define WINDOW_SETTINGS
#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

#include<math.h>
#include <iostream>
#include<string>
#include <algorithm>
#include <filesystem>
#include<cmath>
#include "core.h"

float cot(float i) { return(1 / tanf(i)); }

int main(void)
{
    std::cout << "Lol" << std::endl;
    std::string endp = "/Users/tevz/documents/programing/Zwet-Engine/";
    endp += "/";
    std::replace(endp.begin(), endp.end(), '\\', '/');
    std::cout << endp << std::endl;

    const float resolution[2] = { (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT };

    const float fov = 90.0f;

    const float fovRad = cot(fov * 0.5f / 180.0f * (float)PI);

    const float fNear = 0.1f;

    const float fFar = 1000.0f;

    const float aspectRatio = resolution[1] / resolution[0];

    /*||||||||||||||||||||||||
    ||GAME ENGINE COMPONENTS||
    ||||||||||||||||||||||||*/

    //define game engine
    Engine gameEngine((float)WINDOW_WIDTH, (float)WINDOW_HEIGHT, 60.0f);

    //call this before calling any scene operations (trust me :) ).
    gameEngine.setup();

    //create keyboard class for keyboard inputs
    GLFWwindow* window = gameEngine.getWindow();

    //define the scene
    Scene mainScene;

    mainScene.sceneCamera.pos = { 0.0f, 0.0f, 0.0f };

    //add the projection mat to the scene camera
    mainScene.addCameraProjMat(resolution[0], resolution[1], fFar, fNear, fov);

    //create a font
    Font arial(endp + "resources/fonts/segoe.fnt", endp + "resources/fonts/segoe.jpg", (int*)resolution, 0.01);

    //create new game object
    ObjectInfo test;

    //set the object name
    test.name = "test1";

    //test.enablePhysics = true;

    test.physicsObject.mass = 2.0f;

    //set the object position
    test.position = /*{ 0.0f, 0.0f, 0.0f };/**/ { 0.0f, 20.0f, 0.0f };
    test.staticObjectRotation = { PI/2.0f, 0.0f, 0.0f };

    ObjectInfo test2;

    //set the object name
    test2.name = "test2";

    //set the object position
    test2.position = { 0.0f, 0.0f, 2.0f };

    //set color
    //test2.color = { 0.0f, 1.0f, 0.0f };

    Texture tex2(endp + "resources/textures/lol.jpg");

    test2.tex = tex2;

    //enable depth test and apend all paths to shaers / object files
    test2.depthTest = true;
    test2.drawType = GL_STATIC_DRAW;
    test2.objectModelDir = endp + "resources/models/cube2.obj";
    test2.shaderDirs = {
        {
            endp + "resources/shaders/vertCube.glsl",
            GL_VERTEX_SHADER
        },
        {
            endp + "resources/shaders/frag2.glsl",
            GL_FRAGMENT_SHADER
        }
    };

    ObjectInfo test3;

    //set the object name
    test3.name = "test3";

    //set the object position
    test3.position = { -8.0f, 0.0f, 0.0f };

    test3.color = { 1.0f, 1.0f, 1.0f };

    //enable depth test and apend all paths to shaers / object files
    test3.depthTest = true;
    test3.drawType = GL_STATIC_DRAW;
    test3.objectModelDir = endp + "resources/models/pot2.obj";
    test3.shaderDirs = {
        {
            endp + "resources/shaders/vertCube.glsl",
            GL_VERTEX_SHADER
        },
        {
            endp + "resources/shaders/frag.glsl",
            GL_FRAGMENT_SHADER
        }
    };

    ObjectInfo test4;

    test4.name = "car";

    test4.position = { 0.0f, 0.0f, -3.0f };

    Texture tex4(endp + "resources/textures/lowPoly.jpg");

    test4.tex = tex4;

    test4.depthTest = true;
    test4.drawType = GL_STATIC_DRAW;
    test4.objectModelDir = endp + "resources/models/car2.obj";
    test4.shaderDirs = {
        {
            endp + "resources/shaders/vertCube.glsl",
            GL_VERTEX_SHADER
        },
        {
            endp + "resources/shaders/fragTextureLighting.glsl",
            GL_FRAGMENT_SHADER
        }
    };

    //game object to be used for the font parser test (nothing else pls don't do anything else idk what will happen)
    ObjectInfo test5;

    test5.name = "Font test";

    test5.position = { -3.5f, -1.5f, -4.0f };

    arial.appendToObject(&test5);

    arial.appendString("Janova sestra");

    test5.drawType = GL_STATIC_DRAW;

    test5.shaderDirs = {
        {
            endp + "resources/shaders/vertCube.glsl",
            GL_VERTEX_SHADER
        },
        {
            endp + "resources/shaders/frag2.glsl",
            GL_FRAGMENT_SHADER
        }
    };

    ObjectInfo test6;

    test6.name = "Font lmao";

    test6.position = { -1.6f, 2.0f, -4.0f };

    arial.appendToObject(&test6);

    arial.appendString("*Njegova mama*");

    test6.drawType = GL_STATIC_DRAW;

    test6.shaderDirs = {
        {
            endp + "resources/shaders/vertCube.glsl",
            GL_VERTEX_SHADER
        },
        {
            endp + "resources/shaders/frag2.glsl",
            GL_FRAGMENT_SHADER
        }
    };

    ObjectInfo test7;

    test7.name = "room";

    test7.position = { 0.0f, 0.0f, 5.0f };

    test7.tex = tex4;

    test7.depthTest = true;
    test7.drawType = GL_STATIC_DRAW;
    test7.objectModelDir = endp + "resources/models/room1.obj";
    test7.shaderDirs = {
        {
            endp + "resources/shaders/vertCube.glsl",
            GL_VERTEX_SHADER
        },
        {
            endp + "resources/shaders/fragTextureLighting.glsl",
            GL_FRAGMENT_SHADER
        }
    };

    //add the object to the game scene
    mainScene.addGameObject(test5);

    mainScene.addGameObject(test6);

    mainScene.addGameObject(test7);

    mainScene.addGameObject(test);

    //mainScene.addGameObject(test2);

    //mainScene.addGameObject(test3);

    mainScene.addGameObject(test4);

    //add a step function to the added object
    //TIP: the square brackets at the start of the enclosed function is the capture list (put the shit you want to be scoped to it in there)
    mainScene.setStepFunction(test.name, [window](std::map<std::string, ObjectInfo>& objects, std::string self, Camera& cam) {
        /*movement mods for by how muh it should increase the movement speed*/
        const float movementMod = 0.08f;
        const float yawMod = 0.03f;

        //camera controls for yaw and pitch
        cam.pitch += (-yawMod * kbi::isKeyHeld(window, GLFW_KEY_DOWN) + yawMod * kbi::isKeyHeld(window, GLFW_KEY_UP));
        cam.yaw += (-yawMod * kbi::isKeyHeld(window, GLFW_KEY_RIGHT) + yawMod * kbi::isKeyHeld(window, GLFW_KEY_LEFT));

        //camera controls for movement
        cam.pos.y += (movementMod * kbi::isKeyHeld(window, GLFW_KEY_SPACE)) + (-movementMod * kbi::isKeyHeld(window, GLFW_KEY_LEFT_SHIFT));
        cam.forward = ((movementMod * kbi::isKeyHeld(window, GLFW_KEY_W)) + (-movementMod * kbi::isKeyHeld(window, GLFW_KEY_S)));
        cam.sideways = ((-movementMod * kbi::isKeyHeld(window, GLFW_KEY_A)) + (movementMod * kbi::isKeyHeld(window, GLFW_KEY_D)));

        //objects[self].objectFloats["pitch"] += (-yawMod * kbi::isKeyHeld(window, 'J') + yawMod * kbi::isKeyHeld(window, 'N'));
        //objects[self].objectFloats["yaw"] += (-yawMod * kbi::isKeyHeld(window, 'B') + yawMod * kbi::isKeyHeld(window, 'M'));

        int yaw = glGetUniformLocation(objects[self].program, "objYaw");
        int pitch = glGetUniformLocation(objects[self].program, "objPitch");

        vecs::mat4 objYaw = vc::rotY(objects[self].objectFloats["yaw"]);
        vecs::mat4 objPicth = vc::rotX(objects[self].objectFloats["pitch"]);

        glUniformMatrix4fv(yaw, 1, GL_FALSE, &objYaw.r[0][0]);
        glUniformMatrix4fv(pitch, 1, GL_FALSE, &objPicth.r[0][0]);

        });

    /*mainScene.setStepFunction(test2.name, [](std::map<std::string, ObjectInfo>& objects, std::string self, Camera& cam) {
        });*/

    /*mainScene.setStepFunction(test3.name, [](std::map<std::string, ObjectInfo>& objects, std::string self, Camera& cam) {
        });*/

    mainScene.setStepFunction(test4.name, [](std::map<std::string, ObjectInfo>& objects, std::string self, Camera& cam) {
        });

    mainScene.setStepFunction(test5.name, [](std::map<std::string, ObjectInfo>& objects, std::string self, Camera& cam) {
        });

    mainScene.setStepFunction(test6.name, [](std::map<std::string, ObjectInfo>& objects, std::string self, Camera& cam) {
        });

    mainScene.setStepFunction(test7.name, [](std::map<std::string, ObjectInfo>& objects, std::string self, Camera& cam) {
        });

    mainScene.setCreateFunction(test.name, [](std::map<std::string, ObjectInfo>& objects, std::string self, Camera& cam) {
            objects[self].objectFloats.insert(std::pair<std::string, float>("yaw", 0.0f));
            objects[self].objectFloats.insert(std::pair<std::string, float>("pitch", 0.0f));
        });

    gameEngine.setScene(mainScene);

    gameEngine.run();

    return 0;
}