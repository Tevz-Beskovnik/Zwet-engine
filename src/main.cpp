#include <iostream>
#include<string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<math.h>
#include<cmath>
#include "../includes/scene.h"

#define PI 3.14159265358979323846

float cot(float i) { return(1 / tanf(i)); }

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library*/
    if (!glfwInit())
         return -1;

    /* Create a windowed mode window and its OpenGL context*/

    float horiz, vertical;

    screenResolution(horiz, vertical);

    const float resolution[2] = { horiz, vertical };

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

    Scene mainScene;

    ObjectInfo test;
    test.name = "test1";
    test.position = { 0.0f, 0.0f, 0.0f };
    test.depthTest = true;
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

    createMesh(test);
    createObjectShaders(GL_STATIC_DRAW, test);

    mainScene.setGameObject(test);

    mainScene.setCreateFunction(test.name, [](std::map<std::string, ObjectInfo>& objects, std::string self) {
            float horiz, vertical;

            screenResolution(horiz, vertical);

            const float resolution[2] = { horiz, vertical };

            const float fov = 90.0f;

            const float fovRad = cot(fov * 0.5f / 180.0f * (float)PI);

            const float fNear = 0.1f;

            const float fFar = 1000.0f;

            const float aspectRatio = resolution[1] / resolution[0];

            //define all intagers
            addInt("time", glGetUniformLocation(objects[self].program, "uTime"), objects[self]);
            addInt("projMat", glGetUniformLocation(objects[self].program, "uProjMat"), objects[self]);
            addInt("uWorld", glGetUniformLocation(objects[self].program, "uWorld"), objects[self]);
            addInt("uWorldInvTran", glGetUniformLocation(objects[self].program, "uWorldInvTran"), objects[self]);
            addInt("uCameraPos", glGetUniformLocation(objects[self].program, "uCameraPos"), objects[self]);

            addFloat("yaw", 0.0f, objects[self]);
            addFloat("pitch", 0.0f, objects[self]);

            addVec("vCamera", { 0.0f, 0.0f, 0.0f }, objects[self]);
            addVec("vLookDir", { 0.0f, 0.0f, 1.0f }, objects[self]);
            addVec("vLookDirSqued", { 1.0f, 0.0f, 0.0f }, objects[self]);
            addVec("vUp", { 0.0f, 1.0f, 0.0f }, objects[self]);

            addMat("mProjMat", {
                aspectRatio * fovRad, 0.0f, 0.0f, 0.0f,
                0.0f, fovRad, 0.0f, 0.0f,
                0.0f, 0.0f, fFar / (fFar - fNear), 1.0f,
                0.0f, 0.0f, (-fFar * fNear) / (fFar - fNear), 0.0f
                }, objects[self]);
            addMat("mWorld", createWorldMatrix(0.0f, 0.0f, 0.0f), objects[self]);

            glUseProgram(objects[self].program);
        });

    mainScene.setStepFunction(test.name, [](std::map<std::string, ObjectInfo>& objects, std::string self) {
        /*movement mods for by how much it should increase the movement speed*/
        const float movementMod = 0.03f;
        const float yawMod = 0.02f;

        //camera controls for yaw and pitch
        objects[self].objectFloats["pitch"] += (-yawMod * kbi::isKeyHeld(VK_DOWN) + yawMod * kbi::isKeyHeld(VK_UP));
        objects[self].objectFloats["yaw"] += (-yawMod * kbi::isKeyHeld(VK_RIGHT) + yawMod * kbi::isKeyHeld(VK_LEFT));

        //camera controls for movement
        objects[self].objectVectors["vCamera"].y += (movementMod * kbi::isKeyHeld(VK_SPACE)) + (-movementMod * kbi::isKeyHeld(VK_SHIFT));
        vecs::vec3 vForward = objects[self].objectVectors["vLookDir"] * ((movementMod * kbi::isKeyHeld('W')) + (-movementMod * kbi::isKeyHeld('S')));
        vecs::vec3 vSideways = objects[self].objectVectors["vLookDirSqued"] * ((-movementMod * kbi::isKeyHeld('A')) + (movementMod * kbi::isKeyHeld('D')));

        objects[self].objectVectors["vCamera"] = objects[self].objectVectors["vCamera"] + vForward;
        objects[self].objectVectors["vCamera"] = objects[self].objectVectors["vCamera"] + vSideways;

        vecs::vec3 vTarget = { 0.0f, 0.0f, 1.0f };
        vecs::vec3 vTarget2 = { 1.0f, 0.0f, 0.0f };

        vecs::mat4 mCameraRot = vc::rotY(objects[self].objectFloats["yaw"]);
        objects[self].objectVectors["vLookDir"] = vc::customVecMultiply(mCameraRot, vTarget);
        objects[self].objectVectors["vLookDirSqued"] = vc::customVecMultiply(mCameraRot, vTarget2);
        vTarget = objects[self].objectVectors["vCamera"] + objects[self].objectVectors["vLookDir"];

        //create the end view matrix
        vecs::mat4 mView = createViewMatrix(objects[self].objectMats["mProjMat"], objects[self].objectVectors["vCamera"], vTarget, objects[self].objectVectors["vUp"], objects[self].objectFloats["pitch"]);

        //create transposed inverted matrix
        vecs::mat4 mWorldInvTrans = vc::transposeMat(vc::quickInverse(objects[self].objectMats["mWorld"]));

        glUniform1f(objects[self].objectInts["time"], float(0));

        glUniformMatrix4fv(objects[self].objectInts["uWorld"], 1, GL_FALSE, &(objects[self].objectMats["mWorld"].r[0][0]));

        glUniformMatrix4fv(objects[self].objectInts["projMat"], 1, GL_FALSE, &mView.r[0][0]);

        glUniformMatrix4fv(objects[self].objectInts["uWorldInvTran"], 1, GL_FALSE, &mWorldInvTrans.r[0][0]);

        glUniform3f(objects[self].objectInts["uCameraPos"], objects[self].objectVectors["vCamera"].x, objects[self].objectVectors["vCamera"].y, objects[self].objectVectors["vCamera"].z);
        });

    mainScene.callCreateFunction(test.name);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        mainScene.callStepFunction(test.name);

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