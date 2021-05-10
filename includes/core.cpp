#include"core.h"

Engine::Engine(float width, float height)
{
	//set the windows width and height
	windowHeight = height;
	windowWidth = width;

	// Initialize the library
	if (!glfwInit())
		throw "GLFW failed to initiate.";

	//set the window
	engineWindow = glfwCreateWindow((int)windowWidth, (int)windowHeight, "Window", NULL, NULL);
}

void Engine::run()
{
	//initialize glfw and the window
	initEngineWindow();

	//execute all things that have to happend at create time
	create();

	while (!glfwWindowShouldClose(engineWindow))
	{
		//execute all the things that have to happend at frame
		frame();

		// Swap front and back buffers
		glfwSwapBuffers(engineWindow);

		// Poll for and process events
		glfwPollEvents();
	}

	endEngineWindow();
}

Scene& Engine::getScene()
{
	//return the refrence to the games scene
	return gameScene;
}

void Engine::frame()
{
	//call scene step function
	gameScene.sceneStep();

	//call step function for each object
	for (const auto& objectName : sceneObjectNames)
	{
		gameScene.callStepFunction(objectName);
	}
}

void Engine::create()
{
	//get a list of all the object names
	sceneObjectNames = gameScene.objectNames();

	//call scene create function
	gameScene.sceneCreate();

	//call create function for all of the objects
	for (const auto& objectName : sceneObjectNames)
	{
		gameScene.callCreateFunction(objectName);
	}
}

void Engine::initEngineWindow()
{
	if (!engineWindow)
	{
		glfwTerminate();
		throw "Window failed to initiate";
	}

	/* Make the window's context current*/
	glfwMakeContextCurrent(engineWindow);

	if (glewInit() != GLEW_OK)
		std::cout << "Glew error!" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;
}

void Engine::endEngineWindow()
{
	glfwTerminate();
}