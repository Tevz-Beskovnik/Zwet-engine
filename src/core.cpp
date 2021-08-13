#include"core.h"

double old = 0;
void blockFramerate(float fpsCap) {
	if (old == 0) {
		old = glfwGetTime();
	}
	while (glfwGetTime() - old < 1.0 / fpsCap) {
	}
	old = glfwGetTime();
}

Engine::Engine(float width, float height, float fpsCap)
	:windowWidth(width), windowHeight(height), currentTime(glfwGetTime()), lastTime(0), deltaTime(currentTime - lastTime), fpsCap(fpsCap)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
 	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2); 
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Initialize the library
	if (!glfwInit())
		throw "GLFW failed to initiate.";

	std::cout << "GLFW initiated." << std::endl;

	//set the window
	engineWindow = glfwCreateWindow((int)windowWidth, (int)windowHeight, "game_engin", NULL, NULL);
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

	endEngineWindow();
}

void Engine::setScene(Scene sc)
{
	//return the refrence to the games scene
	gameScene = sc;
}

void Engine::frame()
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

	char *GL_version=(char *)glGetString(GL_VERSION);
    char *GL_vendor=(char *)glGetString(GL_VENDOR);
    char *GL_renderer=(char *)glGetString(GL_RENDERER);

	std::cout << "GL version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

void Engine::endEngineWindow()
{
	glfwTerminate();
}

void Engine::getEngineResolution(int& screenWidth, int& screenHeight) // get the windiow size of the engine
{
	screenWidth = windowWidth;
	screenHeight = windowHeight;
}

GLFWwindow* Engine::getWindow()
{
	return engineWindow;
}