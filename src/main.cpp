#ifndef PI
    #define PI 3.14159265358979323846
#endif // PI

#include<math.h>
#include <iostream>
#include<string>
#include<windows.h>
#include <GL/glew.h>
#include <algorithm>
#include <GLFW/glfw3.h>
#include <filesystem>
#include<cmath>
#include "../includes/core.h"
namespace fs = std::filesystem;

float cot(float i) { return(1 / tanf(i)); }

int main(void)
{
    std::u8string path_string(fs::current_path().u8string());
    std::string endp(path_string.begin(), path_string.end());
    endp += "/";
    std::replace(endp.begin(), endp.end(), '\\', '/');
    std::cout << endp;

    float horiz, vertical;

    screenResolution(horiz, vertical);

    const float resolution[2] = { horiz, vertical };

    const float fov = 90.0f;

    const float fovRad = cot(fov * 0.5f / 180.0f * (float)PI);

    const float fNear = 0.1f;

    const float fFar = 1000.0f;

    const float aspectRatio = resolution[1] / resolution[0];

    /*||||||||||||||||||||||||
    ||GAME ENGINE COMPONENTS||
    ||||||||||||||||||||||||*/

    //define game engine
    Engine gameEngine(1920.0f, 1080.0f);

    //call this before calling any scene operations (trust me :) ).
    gameEngine.setup();

    //define the scene
    Scene mainScene;

    mainScene.sceneCamera.pos = { 0.0f, 0.0f, 0.0f };

    //add the projection mat to the scene camera
    mainScene.addCameraProjMat(resolution[0], resolution[1], fFar, fNear, fov);

    //create new game object
    ObjectInfo test;

    //set the object name
    test.name = "test1";

    //set the object position
    test.position = /*{ 0.0f, 0.0f, 0.0f };/**/ { 0.0f, -4.0f, 4.0f };
    test.staticObjectRotation = { PI/2.0f, 0.0f, 0.0f };

    //set the color
    test.color = { 1.0f, 0.0f, 0.0f };

    Texture newTex(endp + "includes/shaders/textures/JermaSus.jpg");

    test.tex = newTex;

    //enable depth test and apend all paths to shaers / object files
    test.depthTest = true;
    test.drawType = GL_STATIC_DRAW;
    test.objectModelDir = endp + "includes/shaders/models/ship7.obj";
    test.shaderDirs = {
        {
            endp + "includes/shaders/cube/vertShip.glsl",
            GL_VERTEX_SHADER
        },
        {
            endp + "includes/shaders/cube/frag2.glsl",
            GL_FRAGMENT_SHADER
        },
        {
            endp + "includes/shaders/cube/geom2.glsl",
            GL_GEOMETRY_SHADER
        }
    };

    ObjectInfo test2;

    //set the object name
    test2.name = "test2";

    //set the object position
    test2.position = { 8.0f, 1.0f, 0.0f };

    //set color
    //test2.color = { 0.0f, 1.0f, 0.0f };

    Texture tex2(endp + "includes/shaders/textures/JermaSus.jpg");

    test2.tex = tex2;

    //enable depth test and apend all paths to shaers / object files
    test2.depthTest = true;
    test2.drawType = GL_STATIC_DRAW;
    test2.objectModelDir = endp + "includes/shaders/models/cube2.obj";
    test2.shaderDirs = {
        {
            endp + "includes/shaders/cube/vertCube.glsl",
            GL_VERTEX_SHADER
        },
        {
            endp + "includes/shaders/cube/frag2.glsl",
            GL_FRAGMENT_SHADER
        },
        {
            endp + "includes/shaders/cube/geom2.glsl",
            GL_GEOMETRY_SHADER
        }
    };

    ObjectInfo test3;

    //set the object name
    test3.name = "test3";

    //set the object position
    test3.position = { -8.0f, -1.0f, 2.0f };

    //enable depth test and apend all paths to shaers / object files
    test3.depthTest = true;
    test3.drawType = GL_STATIC_DRAW;
    test3.objectModelDir = endp + "includes/shaders/models/pot2.obj";
    test3.shaderDirs = {
        {
            endp + "includes/shaders/cube/vert.glsl",
            GL_VERTEX_SHADER
        },
        {
            endp + "includes/shaders/cube/frag.glsl",
            GL_FRAGMENT_SHADER
        },
        {
            endp + "includes/shaders/cube/geom.glsl",
            GL_GEOMETRY_SHADER
        }
    };

    ObjectInfo test4;

    //set the object position
    test4.position = { 0.0f, 0.0f, 0.0f };
    test4.color = { 1.0f, 1.0f, 0.0f };

    //enable depth test and apend all paths to shaers / object files
    test4.depthTest = true;
    test4.drawType = GL_STATIC_DRAW;
    test4.objectModelDir = endp + "includes/shaders/models/cube.obj";
    test4.shaderDirs = {
        {
            endp + "includes/shaders/cube/vertCube.glsl",
            GL_VERTEX_SHADER
        },
        {
            endp + "includes/shaders/cube/frag.glsl",
            GL_FRAGMENT_SHADER
        },
        {
            endp + "includes/shaders/cube/geom.glsl",
            GL_GEOMETRY_SHADER
        }
    };

    //add the object to the game scene
    mainScene.addGameObject(test);

    mainScene.addGameObject(test2);

    mainScene.addGameObject(test3);

    //mainScene.addGameObject(test4);

    //add a step function to the added object
    mainScene.setStepFunction(test.name, [](std::map<std::string, ObjectInfo>& objects, std::string self, Camera& cam) {
        /*movement mods for by how much it should increase the movement speed*/
        const float movementMod = 0.13f;
        const float yawMod = 0.02f;

        //camera controls for yaw and pitch
        cam.pitch += (-yawMod * kbi::isKeyHeld(VK_DOWN) + yawMod * kbi::isKeyHeld(VK_UP));
        cam.yaw += (-yawMod * kbi::isKeyHeld(VK_RIGHT) + yawMod * kbi::isKeyHeld(VK_LEFT));

        //camera controls for movement
        cam.pos.y += (movementMod * kbi::isKeyHeld(VK_SPACE)) + (-movementMod * kbi::isKeyHeld(VK_SHIFT));
        cam.forward = ((movementMod * kbi::isKeyHeld('W')) + (-movementMod * kbi::isKeyHeld('S')));
        cam.sideways = ((-movementMod * kbi::isKeyHeld('A')) + (movementMod * kbi::isKeyHeld('D')));

        /*objects[self].position.y += (movementMod * kbi::isKeyHeld(VK_SPACE)) + (-movementMod * kbi::isKeyHeld(VK_SHIFT));
        objects[self].position.z += ((movementMod * kbi::isKeyHeld('W')) + (-movementMod * kbi::isKeyHeld('S')));
        objects[self].position.x += ((-movementMod * kbi::isKeyHeld('A')) + (movementMod * kbi::isKeyHeld('D')));*/

        objects[self].objectFloats["pitch"] += (-yawMod * kbi::isKeyHeld('J') + yawMod * kbi::isKeyHeld('N'));
        objects[self].objectFloats["yaw"] += (-yawMod * kbi::isKeyHeld('B') + yawMod * kbi::isKeyHeld('M'));

        int yaw = glGetUniformLocation(objects[self].program, "objYaw");
        int pitch = glGetUniformLocation(objects[self].program, "objPitch");

        vecs::mat4 objYaw = vc::rotY(objects[self].objectFloats["yaw"]);
        vecs::mat4 objPicth = vc::rotX(objects[self].objectFloats["pitch"]);

        glUniformMatrix4fv(yaw, 1, GL_FALSE, &objYaw.r[0][0]);
        glUniformMatrix4fv(pitch, 1, GL_FALSE, &objPicth.r[0][0]);
        });

    mainScene.setStepFunction(test2.name, [](std::map<std::string, ObjectInfo>& objects, std::string self, Camera& cam) {
        });

    mainScene.setStepFunction(test3.name, [](std::map<std::string, ObjectInfo>& objects, std::string self, Camera& cam) {
        });

    /*mainScene.setStepFunction(test4.name, [](std::map<std::string, ObjectInfo>& objects, std::string self, Camera& cam) {
        const float movementMod = 0.03f;

        objects[self].position.y += (movementMod * kbi::isKeyHeld(VK_SPACE)) + (-movementMod * kbi::isKeyHeld(VK_SHIFT));
        objects[self].position.z += ((movementMod * kbi::isKeyHeld('W')) + (-movementMod * kbi::isKeyHeld('S')));
        objects[self].position.x += ((-movementMod * kbi::isKeyHeld('A')) + (movementMod * kbi::isKeyHeld('D')));
        });*/

    mainScene.setCreateFunction(test.name, [](std::map<std::string, ObjectInfo>& objects, std::string self, Camera& cam) {
            objects[self].objectFloats.insert(std::pair<std::string, float>("yaw", 0.0f));
            objects[self].objectFloats.insert(std::pair<std::string, float>("pitch", 0.0f));
        });

    gameEngine.setScene(mainScene);

    gameEngine.run();

    _CrtDumpMemoryLeaks();
    return 0;
}