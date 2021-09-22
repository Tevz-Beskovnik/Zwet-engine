#include <application.h>

namespace ZWET
{
	double old = 0;
	void blockFramerate(float fpsCap) {
		if (old == 0) {
			old = glfwGetTime();
		}
		while (glfwGetTime() - old < 1.0 / fpsCap) {
		}
		old = glfwGetTime();
	}

	Application::Application()
		:currentTime(glfwGetTime()), lastTime(0), deltaTime(currentTime - lastTime), fpsCap(60), engineWindow(Window::create(800, 600))
	{
		;
	}

	void Application::run()
	{
		
		//execute all things that have to happend at create time
		renderer->init();

		
		while (!glfwWindowShouldClose(engineWindow))
		{
			
			blockFramerate(fpsCap);

			
			renderer->frame();

		}

		Window::close();
	}

	void Application::setScene(Scene& scene)
	{
		renderer = CreateUnique<Renderer>(scene, 60, engineWindow);
	}

	void Application::setFpsCap(float fpsCap)
	{
		fpsCap = fpsCap;
	}

	void Application::setWindowDims(size_t width, size_t height)
	{
		Window::resize(engineWindow, width, height);
	}

	void Application::setup()
	{
		Window::bindWindow(engineWindow);
	}
}