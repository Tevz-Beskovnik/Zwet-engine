#include <iostream>
#include<string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<math.h>
#include<cmath>
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

    const float resolution[2] = { 1200.0f, 900.0f };

    const float fov = 70.0f;

    const float fovRad = cot(fov * 0.5f / 180.0f * (float)PI);

    const float fNear = 0.1f;

    const float fFar = 1000.0f;

    const float aspectRatio = resolution[1] / resolution[0];

    window = glfwCreateWindow(int(resolution[0]), int(resolution[1]), "Window", NULL, NULL);

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
        {{ 0.5f, -0.5f, 0.5f,    0.5f, 0.5f, 0.5f,    -0.5f, 0.5f, 0.5f }, 0.5f, 0.5f, 0.0f },
        {{ 0.5f, -0.5f, 0.5f,    -0.5f, 0.5f, 0.5f,    -0.5f, -0.5f, 0.5f }, 0.5f, 0.5f, 0.0f },

        // WEST                                                      
        {{ -0.5f, -0.5f, 0.5f,    -0.5f, 0.5f, 0.5f,    -0.5f, 0.5f, -0.5f }, 1.0f, 1.0f, 0.0f },
        {{ -0.5f, -0.5f, 0.5f,    -0.5f, 0.5f, -0.5f,    -0.5f, -0.5f, -0.5f }, 1.0f, 1.0f, 0.0f },

        // TOP                                                       
        {{ -0.5f, 0.5f, -0.5f,    -0.5f, 0.5f, 0.5f,    0.5f, 0.5f, 0.5f }, 1.0f, 0.5f, 0.0f },
        {{ -0.5f, 0.5f, -0.5f,    0.5f, 0.5f, 0.5f,    0.5f, 0.5f, -0.5f }, 1.0f, 0.5f, 0.0f },

        // BOTTOM                                                    
        {{ 0.5f, -0.5f, 0.5f,    -0.5f, -0.5f, 0.5f,    -0.5f, -0.5f, -0.5f }, 1.0f, 0.5f, 0.5f },
        {{ 0.5f, -0.5f, 0.5f,    -0.5f, -0.5f, -0.5f,    0.5f, -0.5f, -0.5f }, 1.0f, 0.5f, 0.5f }

    };/**/

    GLenum type = GL_STATIC_DRAW;

    std::vector<float> convTris;
    
    convertMeshToArray(trig, convTris);

    Viewport myView(vert, frag, geometry, convTris, type);

    unsigned int program = myView.initRender();

    int time = glGetUniformLocation(program, "uTime");
    int projMat = glGetUniformLocation(program, "uProjMat");
    int rotation = glGetUniformLocation(program, "uRot");

    vecs::mat4 projMatC = {
        aspectRatio * fovRad, 0.0f, 0.0f, 0.0f,
        0.0f, fovRad, 0.0f, 0.0f,
        0.0f, 0.0f, fFar / (fFar - fNear), 1.0f,
        0.0f, 0.0f, (-fFar * fNear) / (fFar - fNear), 0.0f
    };

    int timeS = 0;

    float xAxis = 0;
    float zAxis = 0;

    glUseProgram(program);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glUniform1f(time, float(timeS));

        glUniformMatrix4fv(projMat, 1, GL_FALSE, &projMatC.r[0][0]);

        glUniform2f(rotation, xAxis, zAxis);

        xAxis += (0.2f * kbi::isKeyHeld('A')) + (-0.2f * kbi::isKeyHeld('D'));
        zAxis += (0.2f * kbi::isKeyHeld('W')) + (-0.2f * kbi::isKeyHeld('S'));

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