#include"../includes/core.h"

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

void Engine::setup()
{
	//initialize glfw and the window
	initEngineWindow();

	/*
	This has to be initialized beindfore bing any objects to the scene becouse we are calling openGL in the binding
	functions and if the window context is not set before calling the function we get a nasty memory access violation :)))
	*/
}

void Engine::run()
{
	//execute all things that have to happend at create time
	create();

	while (!glfwWindowShouldClose(engineWindow))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);

		//execute all the things that have to happend at frame
		frame();

		// Swap front and back buffers
		glfwSwapBuffers(engineWindow);

		// Poll for and process events
		glfwPollEvents();
	}

	endEngineWindow();
}

void Engine::setScene(Scene sc)
{
	//return the refrence to the games scene
	gameScene = sc;
}

void Engine::frame()
{
	//call step function for each object
	for (const auto& objectName : sceneObjectNames)
	{
		gameScene.callStepFunction(objectName);
	}

	//call scene step function
	gameScene.sceneStep();
}

void Engine::create()
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