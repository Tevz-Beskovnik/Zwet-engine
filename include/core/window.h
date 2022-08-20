#pragma once

#include <core.h>

namespace ZWET
{
    struct WindowHints{

    };

    class Window
    {
        public: 
            Window();

            ~Window();

            static GLFWwindow* create(size_t width, size_t height);

            static void bindWindow(GLFWwindow* window);

            static void resize(GLFWwindow* window, size_t width, size_t height);

            static int* getSize(GLFWwindow* window);

            static void close();
    };
}