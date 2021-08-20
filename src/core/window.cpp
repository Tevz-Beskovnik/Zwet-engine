#include <window.h>

namespace ZWET
{
    GLFWwindow* Window::create(size_t width = 800, size_t height = 600)
    {
        // Initialize the library
		if (!glfwInit())
			throw "GLFW failed to initiate.";

		std::cout << "GLFW initiated." << std::endl;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	 	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2); 
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		//set the window
		return glfwCreateWindow((int)width, (int)height, "ZWET_Engine", NULL, NULL);
    }

    void Window::bindWindow(GLFWwindow* window)
    {
        if (!window)
		{
			glfwTerminate();
			throw "Window failed to initiate";
		}

		glfwMakeContextCurrent(window);
    }

    void Window::close()
    {
        glfwTerminate();
    }
}