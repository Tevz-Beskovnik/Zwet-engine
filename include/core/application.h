#include <core.h>

#include <sceneCore.h>
#include <window.h>

namespace ZWET
{
    class Application {
    	/*TODO
    		-add physics engine (obably runs on own clock),
    		-ect...
    	*/
    	public:
    		Application(size_t, size_t, bool);
    
    		void setup();

    		void run();
    
    		void setScene(Scene);
    
    	private:
    		Scene gameScene;

    		GLFWwindow* engineWindow;
    		float fpsCap;
    		float currentTime, lastTime, deltaTime;
    		std::vector<std::string> sceneObjectNames;
    
    		void frame();
    
    		void create();
    };
}