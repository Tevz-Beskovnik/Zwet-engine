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

            static GLFWwindow* create(size_t width = 800, size_t height = 600);

            static void bindWindow(GLFWwindow*);

            static void close();
    };
}