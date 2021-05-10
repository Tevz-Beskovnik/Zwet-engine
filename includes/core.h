#pragma once
#ifndef PI
	#define PI 3.14159265358979323846
#endif // PI

#include<math.h>
#include <iostream>
#include<string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<cmath>
#include"scene.h"

class Engine {
	/*
		-detach main game loop from the main file (for ease of use),
			-this will be done here when the run() function is called will have internal loop,
			-maybe add it as a timer ¯\_(ツ)_/¯ (have no clue how to do that),
		-detach calling step function from main game loop (for ease of use),
			-don't realy know how to do that with my current object - scene system
			-i'll do it with a for loop for now but not sure how to do it to make if more afficient (maybe its gonna be fine this way)
	*/
	public:
		Engine(float, float);
	
		void run();
	
		Scene& getScene();
	
	private:
		Scene gameScene;
		GLFWwindow* engineWindow;
		float windowHeight = 600.0f;
		float windowWidth = 800.0f;
		std::vector<std::string> sceneObjectNames;
	
		void initEngineWindow();

		void endEngineWindow();
	
		void frame();
	
		void create();
};