#ifndef PI
    #define PI 3.14159265358979323846
#endif // PI

#include<math.h>
#include <iostream>
#include<string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<cmath>
#include "../includes/scene.h"

float cot(float i) { return(1 / tanf(i)); }

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library*/
    if (!glfwInit())
         return -1;

    //things to do with projection matrix

    float horiz, vertical;

    screenResolution(horiz, vertical);

    const float resolution[2] = { horiz, vertical };

    const float fov = 90.0f;

    const float fovRad = cot(fov * 0.5f / 180.0f * (float)PI);

    const float fNear = 0.1f;

    const float fFar = 1000.0f;

    const float aspectRatio = resolution[1] / resolution[0];

    /* Create a windowed mode window and its OpenGL context*/

    window = glfwCreateWindow((int)resolution[0], (int)resolution[1], "Window", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current*/
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        std::cout << "Glew error!" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    /*||||||||||||||||||||||||
    ||GAME ENGINE COMPONENTS||
    ||||||||||||||||||||||||*/

    //define the scene
    Scene mainScene;

    //add the projection mat to the scene camera
    mainScene.addCameraProjMat(resolution[0], resolution[1], fFar, fNear, fov);

    //create new game object
    ObjectInfo test;

    //set the object name
    test.name = "test1";

    //set the object position
    test.position = { 0.0f, 0.0f, 4.0f };

    //enable depth test and apend all paths to shaers / object files
    test.depthTest = true;
    test.drawType = GL_STATIC_DRAW;
    test.objectModelDir = "C:/Users/tevzb/Desktop/koda/physics_engine/3D_voxel_physics/Project1/includes/shaders/models/ship2.obj";
    test.shaderDirs = {
        {
            "C:/Users/tevzb/Desktop/koda/physics_engine/3D_voxel_physics/Project1/includes/shaders/cube/vert.glsl",
            GL_VERTEX_SHADER
        },
        {
            "C:/Users/tevzb/Desktop/koda/physics_engine/3D_voxel_physics/Project1/includes/shaders/cube/frag.glsl",
            GL_FRAGMENT_SHADER
        },
        {
            "C:/Users/tevzb/Desktop/koda/physics_engine/3D_voxel_physics/Project1/includes/shaders/cube/geom.glsl",
            GL_GEOMETRY_SHADER
        }
    };

    //add the object to the game scene
    mainScene.setGameObject(test);

    //add a create function to the added object
    mainScene.setCreateFunction(test.name, [](std::map<std::string, ObjectInfo>& objects, std::string self, Camera& cam) {
            glUseProgram(objects[self].program);
        });

    //add a step function to the added object
    mainScene.setStepFunction(test.name, [](std::map<std::string, ObjectInfo>& objects, std::string self, Camera& cam) {
        /*movement mods for by how much it should increase the movement speed*/
        const float movementMod = 0.03f;
        const float yawMod = 0.02f;

        //camera controls for yaw and pitch
        cam.pitch += (-yawMod * kbi::isKeyHeld(VK_DOWN) + yawMod * kbi::isKeyHeld(VK_UP));
        cam.yaw += (-yawMod * kbi::isKeyHeld(VK_RIGHT) + yawMod * kbi::isKeyHeld(VK_LEFT));

        //camera controls for movement
        cam.pos.y += (movementMod * kbi::isKeyHeld(VK_SPACE)) + (-movementMod * kbi::isKeyHeld(VK_SHIFT));
        cam.forward = ((movementMod * kbi::isKeyHeld('W')) + (-movementMod * kbi::isKeyHeld('S')));
        cam.sideways = ((-movementMod * kbi::isKeyHeld('A')) + (movementMod * kbi::isKeyHeld('D')));
        });

    //calling the create function
    mainScene.callCreateFunction(test.name);

    //calling the scenes create function
    mainScene.sceneCreate();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        //calling the objects step function
        mainScene.callStepFunction(test.name);

        //calling the scenes step function
        mainScene.sceneStep();

        /* Render here */
        //glClearColor(0.537f, 0.796f, 0.9803f, 1.0f);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, mainScene.totalTris / 6);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}