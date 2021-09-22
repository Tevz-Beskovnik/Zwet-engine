#include <window.h>
#include <log.h>

namespace ZWET
{
    GLFWwindow* Window::create(size_t width = 800, size_t height = 600)
    {
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	 	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Initialize the library
		if (!glfwInit())
			throw "GLFW failed to initiate.";

		std::cout << "GLFW initiated." << std::endl;

		//set the window
		ZWET_INFO("About to create window");

		return glfwCreateWindow((int)width, (int)height, "ZWET_Engine", NULL, NULL);
    }

    void Window::bindWindow(GLFWwindow* window)
    {
		ZWET_INFO("About to bind window");

        if (!window)
		{
			glfwTerminate();
			throw "Window failed to initiate";
		}

		glfwMakeContextCurrent(window);

		ZWET_INFO("Window binded");

		if (glewInit() != GLEW_OK)
			std::cout << "Glew error!" << std::endl;

		char *GL_version=(char *)glGetString(GL_VERSION);
    	char *GL_vendor=(char *)glGetString(GL_VENDOR);
    	char *GL_renderer=(char *)glGetString(GL_RENDERER);

		std::cout << "GL version: " << glGetString(GL_VERSION) << std::endl;
		std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

		ZWET_INFO("GLEW initiated");
    }

    void Window::close()
    {
        glfwTerminate();
    }

	void Window::resize(GLFWwindow* window, size_t width, size_t height)
	{
		glfwSetWindowSize(window, width, height);
	}

	int* Window::getSize(GLFWwindow* window)
	{
		int* dimensions = (int*)malloc(2 * sizeof(int));

		glfwGetWindowSize(window , &dimensions[0], &dimensions[1]);

		return dimensions;
	}
}