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

    std::string vert = "C:/Users/tevzb/Desktop/koda/physics_engine/3D_voxel_physics/Project1/includes/shaders/vert.glsl";
    std::string frag = "C:/Users/tevzb/Desktop/koda/physics_engine/3D_voxel_physics/Project1/includes/shaders/frag.glsl";
    std::string geometry = "C:/Users/tevzb/Desktop/koda/physics_engine/3D_voxel_physics/Project1/includes/shaders/geom.glsl";
    vecs::mesh trig;

    trig.tris = {

        // SOUTH
        {{ -0.5f, -0.5f, -0.5f,    -0.5f, 0.5f, -0.5f,    0.5f, 0.5f, -0.5f }, 1.0f, 0.5f, 0.0f },
        {{ -0.5f, -0.5f, -0.5f,    0.5f, 0.5f, -0.5f,    0.5f, -0.5f, -0.5f }, 1.0f, 0.5f, 0.0f },
        
        // EAST                                                      
        {{ 0.5f, -0.5f, -0.5f,    0.5f, 0.5f, -0.5f,    0.5f, 0.5f, 0.5f }, 1.0f, 0.5f, 0.0f },
        {{ 0.5f, -0.5f, -0.5f,    0.5f, 0.5f, 0.5f,    0.5f, -0.5f, 0.5f }, 1.0f, 0.5f, 0.0f },

        // NORTH                                                     
        {{ 0.5f, -0.5f, 0.5f,    0.5f, 0.5f, 0.5f,    -0.5f, 0.5f, 0.5f }, 1.0f, 0.5f, 0.0f },
        {{ 0.5f, -0.5f, 0.5f,    -0.5f, 0.5f, 0.5f,    -0.5f, -0.5f, 0.5f }, 1.0f, 0.5f, 0.0f },

        // WEST                                                      
        {{ -0.5f, -0.5f, 0.5f,    -0.5f, 0.5f, 0.5f,    -0.5f, 0.5f, -0.5f }, 1.0f, 0.5f, 0.0f },
        {{ -0.5f, -0.5f, 0.5f,    -0.5f, 0.5f, -0.5f,    -0.5f, -0.5f, -0.5f }, 1.0f, 0.5f, 0.0f },

        // TOP                                                       
        {{ -0.5f, 0.5f, -0.5f,    -0.5f, 0.5f, 0.5f,    0.5f, 0.5f, 0.5f }, 1.0f, 0.5f, 0.0f },
        {{ -0.5f, 0.5f, -0.5f,    0.5f, 0.5f, 0.5f,    0.5f, 0.5f, -0.5f }, 1.0f, 0.5f, 0.0f },

        // BOTTOM                                                    
        {{ 0.5f, -0.5f, 0.5f,    -0.5f, -0.5f, 0.5f,    -0.5f, -0.5f, -0.5f }, 1.0f, 0.5f, 0.0f },
        {{ 0.5f, -0.5f, 0.5f,    -0.5f, -0.5f, -0.5f,    0.5f, -0.5f, -0.5f }, 1.0f, 0.5f, 0.0f }

    };/**/

    GLenum type = GL_STATIC_DRAW;

    std::vector<float> convTris;
    
    convertMeshToArray(trig, convTris);

    Viewport myView(vert, frag, geometry, convTris, type);

    unsigned int program = myView.initRender();

    int time = glGetUniformLocation(program, "uTime");
    int projMat = glGetUniformLocation(program, "uProjMat");
    int uWorld = glGetUniformLocation(program, "uWorld");
    int uView = glGetUniformLocation(program, "uView");
    //int uCameraVec = glGetUniformLocation(program, "uCameraVec");
    //int uTarget = glGetUniformLocation(program, "uTarget");
    //int uCamera = glGetUniformLocation(program, "uCamera");

    int timeS = 0;

    float xAxis = 0;
    float zAxis = 0;

    //directions
    //camera yaw
    float yaw = 0;

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

    glUseProgram(program);

    //world matrix (doesn't realy change so no need to make it multiple times :)
    vecs::mat4 mWorld = myView.createWorldMatrix(1.2f, 1.7f, 1.0f);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        float movementMod = 0.01f;
        float yawMod = 0.02f;

        vCamera.y += (movementMod * kbi::isKeyHeld(VK_UP)) + (-movementMod * kbi::isKeyHeld(VK_DOWN));
        yaw += (-yawMod * kbi::isKeyHeld(VK_RIGHT) + yawMod * kbi::isKeyHeld(VK_LEFT));

        //create the initial
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
        vecs::mat4 mView = myView.createViewMatrix(mProjMat, vCamera, vTarget, vUp);

        glUniform1f(time, float(timeS));

        glUniformMatrix4fv(uWorld, 1, GL_FALSE, &mWorld.r[0][0]);

        glUniformMatrix4fv(projMat, 1, GL_FALSE, &mView.r[0][0]);

        timeS++;

        /* Render here */
        glClearColor(0.35f, 0.45f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, myView.vecSize / 6);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}