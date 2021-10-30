#pragma once

#include <core.h>
#include <scene.h>
#include <renderer.h>
#include <window.h>
#include <utils.h>
#include <log.h>

namespace ZWET
{
    class Application {
    	/*TODO
    		-add physics engine (obably runs on own clock),
    		-ect...
    	*/
    	public:
    		Application();

			void setFpsCap(float fpsCap);

			void setWindowDims(size_t width, size_t height);

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