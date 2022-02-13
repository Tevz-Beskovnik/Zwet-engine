#pragma once

#include <core.h>
#include <scene.h>
#include <renderer.h>
#include <window.h>
#include <utils.h>
#include <log.h>

/*
	TODO:
		- Port the old physics engine and improve it,
		- port the font library
		- do better mesh optimisations for newer OpenGL versions (instanced rendering),
		- rebrand the game engine to Bolt engine (We have a whole logo now goddamn it)
*/

namespace ZWET
{
    class Application {
    	public:
    		Application();

			void setFpsCap(float fpsCap);

			void setWindowDims(size_t width, size_t height);

			void setBackgroundColor(rgb color) { renderer->setBackground(color); };

    		void run();
    
    		void setScene(Scene& scene);

    	private:
    		UniquePtr<Renderer> renderer;

    		GLFWwindow* engineWindow;
    		unsigned int fpsCap;
    		double currentTime, lastTime, deltaTime;
			double old = 0;

			void blockFramerate(float fpsCap);

			void calculateDelta();
    };
}