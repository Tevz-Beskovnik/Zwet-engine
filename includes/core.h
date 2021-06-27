#pragma once
#ifndef PI
	#define PI 3.14159265358979323846
#endif // PI

#ifndef WINDOW_SETTINGS
	#define WINDOW_SETTINGS
	#define WINDOW_WIDTH 800
	#define WINDOW_HEIGHT 600
#endif

#include<math.h>
#include <iostream>
#include<string>
#include<cmath>
#include "fontParser.h"
#include"sceneCore.h"

class Engine {
	/*TODO
		-add physics engine (obably runs on own clock),
		-ect...
	*/
	public:
		Engine(float, float, float fpsCap);
	
		void setup();

		void run();
	
		void setScene(Scene);

		void getEngineResolution(int& screenWidth, int& screenHeight);
	
	private:
		Scene gameScene;

		GLFWwindow* engineWindow;
		float windowHeight = 600.0f;
		float windowWidth = 800.0f;
		float fpsCap;
		float currentTime, lastTime, deltaTime;
		std::vector<std::string> sceneObjectNames;
	
		void initEngineWindow();

		void endEngineWindow();
	
		void frame();
	
		void create();
};