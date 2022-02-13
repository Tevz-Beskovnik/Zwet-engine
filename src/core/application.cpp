#include <application.h>

namespace ZWET
{
	void callbackFunc(int id, const char* desc)
	{
		std::cout << desc << std::endl;
	}

	void Application::blockFramerate(float fpsCap) {
		if (old == 0) {
			old = glfwGetTime();
		}
		while (glfwGetTime() - old < 1.0 / fpsCap) {
		}
		old = glfwGetTime();
	}

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
			calculateDelta();
			blockFramerate(60.0f);
			
			renderer->frame();
		}

		Window::close();
	}

	void Application::setScene(Scene& scene)
	{
		renderer = CreateUnique<Renderer>(scene, 60, engineWindow, deltaTime);
		renderer->setBackground({0.0f, 0.0f, 0.0f}); // white background
	}

	void Application::setFpsCap(float fpsCap)
	{
		fpsCap = fpsCap;
	}

	void Application::setWindowDims(size_t width, size_t height)
	{
		Window::resize(engineWindow, width, height);
	}

	void Application::calculateDelta()
	{
		lastTime = currentTime;
		currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
	}
}