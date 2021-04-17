#include <iostream>
#include<string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<math.h>
#include<cmath>
#include "../includes/vecCalc.h"
#include "../includes/viewport.h"
#include "../includes/kbInput.h"

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

    const float fov = 90.0f;

    const float fovRad = cot(fov * 0.5f / 180.0f * (float)PI);

    const float fNear = 0.1f;

    const float fFar = 1000.0f;

    const float aspectRatio = resolution[1] / resolution[0];

    /*movement mods for by how much it should increase the movement speed*/
    const float movementMod = 0.03f;

    const float yawMod = 0.02f;

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

    std::string vert = "C:/Users/tevzb/Desktop/koda/physics_engine/3D_voxel_physics/Project1/includes/shaders/cube/vert.glsl";
    std::string frag = "C:/Users/tevzb/Desktop/koda/physics_engine/3D_voxel_physics/Project1/includes/shaders/cube/frag.glsl";
    std::string geometry = "C:/Users/tevzb/Desktop/koda/physics_engine/3D_voxel_physics/Project1/includes/shaders/cube/geom.glsl";
    vecs::mesh trig;

    vecs::loadFromObjectFile("C:/Users/tevzb/Desktop/koda/physics_engine/3D_voxel_physics/Project1/includes/shaders/models/ship2.obj", trig);

    /*for (const auto& tri : trig.tris)
    {
        std::cout << tri.normal.x << " " << tri.normal.y << " " << tri.normal.z << std::endl;
    }

    /*trig.tris = {

        // floor
        {{ -5.0f, -0.5f, -5.0f,    -5.0f, -0.5f, 5.0f,    5.0f, -0.5f, 5.0f }, 0.0f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f },
        {{ -5.0f, -0.5f, -5.0f,    5.0f, -0.5f, 5.0f,    5.0f, -0.5f, -5.0f }, 0.0f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f },

        // SOUTH
        {{ -0.5f, -0.5f, -0.5f,    -0.5f, 0.5f, -0.5f,    0.5f, 0.5f, -0.5f }, 1.0f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f },
        {{ -0.5f, -0.5f, -0.5f,    0.5f, 0.5f, -0.5f,    0.5f, -0.5f, -0.5f }, 1.0f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f },
        
        // EAST                                                      
        {{ 0.5f, -0.5f, -0.5f,    0.5f, 0.5f, -0.5f,    0.5f, 0.5f, 0.5f }, 1.0f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f },
        {{ 0.5f, -0.5f, -0.5f,    0.5f, 0.5f, 0.5f,    0.5f, -0.5f, 0.5f }, 1.0f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f },

        // NORTH                                                     
        {{ 0.5f, -0.5f, 0.5f,    0.5f, 0.5f, 0.5f,    -0.5f, 0.5f, 0.5f }, 1.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f },
        {{ 0.5f, -0.5f, 0.5f,    -0.5f, 0.5f, 0.5f,    -0.5f, -0.5f, 0.5f }, 1.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f },

        // WEST                                                      
        {{ -0.5f, -0.5f, 0.5f,    -0.5f, 0.5f, 0.5f,    -0.5f, 0.5f, -0.5f }, 1.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f },
        {{ -0.5f, -0.5f, 0.5f,    -0.5f, 0.5f, -0.5f,    -0.5f, -0.5f, -0.5f }, 1.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f },

        // TOP                                                       
        {{ -0.5f, 0.5f, -0.5f,    -0.5f, 0.5f, 0.5f,    0.5f, 0.5f, 0.5f }, 1.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f },
        {{ -0.5f, 0.5f, -0.5f,    0.5f, 0.5f, 0.5f,    0.5f, 0.5f, -0.5f }, 1.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f },

        // BOTTOM                                                    
        {{ 0.5f, -0.5f, 0.5f,    -0.5f, -0.5f, 0.5f,    -0.5f, -0.5f, -0.5f }, 1.0f, 0.5f, 0.0f, 0.0f, -1.0f, 0.0f },
        {{ 0.5f, -0.5f, 0.5f,    -0.5f, -0.5f, -0.5f,    0.5f, -0.5f, -0.5f }, 1.0f, 0.5f, 0.0f, 0.0f, -1.0f, 0.0f },

        //floor bottom
        {{ 5.0f, -0.5f, 5.0f,    -5.0f, -0.5f, 5.0f,    -5.0f, -0.5f, -5.0f }, 1.0f, 0.5f, 0.0f, 0.0f, -1.0f, 0.0f },
        {{ 5.0f, -0.5f, 5.0f,    -5.0f, -0.5f, -5.0f,    5.0f, -0.5f, -5.0f }, 1.0f, 0.5f, 0.0f, 0.0f, -1.0f, 0.0f },
    };/**/

    GLenum type = GL_STATIC_DRAW;

    std::vector<float> convTris;
    
    convertMeshToArray(trig, convTris);

    Viewport myView(vert, frag, geometry, convTris, type);

    unsigned int program = myView.initRender();

    int time = glGetUniformLocation(program, "uTime");
    int projMat = glGetUniformLocation(program, "uProjMat");
    int uWorld = glGetUniformLocation(program, "uWorld");
    int uWorldInvTran = glGetUniformLocation(program, "uWorldInvTran");
    int uCameraPos = glGetUniformLocation(program, "uCameraPos");

    int timeS = 0;

    float xAxis = 0;
    float zAxis = 0;

    //directions
    //camera yaw
    float yaw = 0;
    float pitch = 0;

    vecs::vec3 vCamera = { 0.0f, 0.0f, 0.0f };

    //look directions
    vecs::vec3 vLookDir = { 0.0f, 0.0f, 1.0f };
    vecs::vec3 vLookDirSqued = { 1.0f, 0.0f, 0.0f };

    vecs::vec3 vUp = { 0.0f, 1.0f, 0.0f };

    //projection mat
    vecs::mat4 mProjMat = 
    {
        aspectRatio * fovRad, 0.0f, 0.0f, 0.0f,
        0.0f, fovRad, 0.0f, 0.0f,
        0.0f, 0.0f, fFar / (fFar - fNear), 1.0f,
        0.0f, 0.0f, (-fFar * fNear) / (fFar - fNear), 0.0f
    };

    //world matrix (doesn't realy change so no need to make it multiple times :)
    vecs::mat4 mWorld = myView.createWorldMatrix(0.0f, 0.0f, 0.0f);

    glUseProgram(program);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        //camera controls for yaw and pitch
        pitch += (-yawMod * kbi::isKeyHeld(VK_DOWN) + yawMod * kbi::isKeyHeld(VK_UP));
        yaw += (-yawMod * kbi::isKeyHeld(VK_RIGHT) + yawMod * kbi::isKeyHeld(VK_LEFT));

        //camera controls for movement
        vCamera.y += (movementMod * kbi::isKeyHeld(VK_SPACE)) + (-movementMod * kbi::isKeyHeld(VK_SHIFT));
        vecs::vec3 vForward = vLookDir * ((movementMod * kbi::isKeyHeld('W')) + (-movementMod * kbi::isKeyHeld('S')));
        vecs::vec3 vSideways = vLookDirSqued * ((-movementMod * kbi::isKeyHeld('A')) + (movementMod * kbi::isKeyHeld('D')));

        vCamera = vCamera + vForward;
        vCamera = vCamera + vSideways;

        vecs::vec3 vTarget = { 0.0f, 0.0f, 1.0f };
        vecs::vec3 vTarget2 = { 1.0f, 0.0f, 0.0f };

        vecs::mat4 mCameraRot = vc::rotY(yaw);
        vLookDir = vc::customVecMultiply(mCameraRot, vTarget);
        vLookDirSqued = vc::customVecMultiply(mCameraRot, vTarget2);
        vTarget = vCamera + vLookDir;
        
        //create the end view matrix
        vecs::mat4 mView = myView.createViewMatrix(mProjMat, vCamera, vTarget, vUp, pitch);

        //create transposed inverted matrix
        vecs::mat4 mWorldInvTrans = vc::transposeMat(vc::quickInverse(mWorld));

        glUniform1f(time, float(timeS));

        glUniformMatrix4fv(uWorld, 1, GL_FALSE, &mWorld.r[0][0]);

        glUniformMatrix4fv(projMat, 1, GL_FALSE, &mView.r[0][0]);

        glUniformMatrix4fv(uWorldInvTran, 1, GL_FALSE, &mWorldInvTrans.r[0][0]);

        glUniform3f(uCameraPos, vCamera.x, vCamera.y, vCamera.z);

        timeS++;

        /* Render here */
        //glClearColor(0.537f, 0.796f, 0.9803f, 1.0f);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, myView.vecSize / 6);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}