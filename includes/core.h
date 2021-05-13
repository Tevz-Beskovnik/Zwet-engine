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
	/*TODO
		-this will be done here when the run() function is called will have internal loop,
		-ect...
	*/
	public:
		Engine(float, float);
	
		void setup();

		void run();
	
		void setScene(Scene);
	
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