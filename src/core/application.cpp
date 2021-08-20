#include <application.h>

double old = 0;
void blockFramerate(float fpsCap) {
	if (old == 0) {
		old = glfwGetTime();
	}
	while (glfwGetTime() - old < 1.0 / fpsCap) {
	}
	old = glfwGetTime();
}

namespace ZWET
{
	Application::Application(size_t width, size_t height, bool vSync)
		:currentTime(glfwGetTime()), lastTime(0), deltaTime(currentTime - lastTime), fpsCap(fpsCap)
	{
		engineWindow = Window::create(width, height);

		Window::bindWindow(engineWindow);
	}

	void Application::run()
	{
		//execute all things that have to happend at create time
		create();

		while (!glfwWindowShouldClose(engineWindow))
		{
			blockFramerate(fpsCap);
			// Poll for and process events
			glfwPollEvents();

			glClearColor(0.36862f, 0.20392f, 0.9215686f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//execute all the things that have to happend at frame
			frame();

			// Swap front and back buffers
			glfwSwapBuffers(engineWindow);
		}

		Window::close();
	}

	void Application::setScene(Scene sc)
	{
		//return the refrence to the games scene
		gameScene = sc;
	}

	void Application::frame()
	{
		currentTime = glfwGetTime();

		deltaTime = currentTime - lastTime;

		//call scene step function
		gameScene.sceneStep(deltaTime);

		//call step function for each object
		for (const auto& objectName : sceneObjectNames)
		{
			gameScene.stepStart(objectName);

			gameScene.callStepFunction(objectName);

			gameScene.stepEnd(objectName);
		}

		lastTime = glfwGetTime();
	}

	void Application::create()
	{
		//get a list of all the object names
		sceneObjectNames = gameScene.objectNames();

		//call create function for all of the objects
		for (const auto& objectName : sceneObjectNames)
		{
			gameScene.callCreateFunction(objectName);
		}

		//call scene create function
		gameScene.sceneCreate();
	}
}