#include <application.h>

namespace ZWET
{
	Application::Application()
		:currentTime(glfwGetTime()), lastTime(0), deltaTime(currentTime - lastTime), fpsCap(60)
	{
		engineWindow = Window::create(800, 600);

		Window::bindWindow(engineWindow);
	}

	void Application::run()
	{
		//execute all things that have to happend at create time
		renderer->init();

		while (!glfwWindowShouldClose(engineWindow))
		{
			renderer->frame();
		}

		Window::close();
	}

	void Application::setScene(Scene& scene)
	{
		renderer = CreateUnique<Renderer>(scene, 60);
	}

	void Application::setFpsCap(unsigned int fpsCap)
	{
		renderer->setFpsCap(fpsCap);
	}

	void Application::setWindowDims(size_t width, size_t height)
	{
		Window::resize(engineWindow, width, height);
	}
}