#include <keyInput.h>

namespace ZWET
{
    KeyboardInput::KeyboardInput(GLFWwindow* window)
        : window(window)
    {
        ;
    }

    KeyboardInput::~KeyboardInput()
    {
        ;
    }

    bool KeyboardInput::isKeyHeld(int key)
    {
        glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_FALSE);
	    int state = glfwGetKey(window, key);
	    if(state == GLFW_PRESS)
	    	return true;
	    else
	    	return false;
    }

	bool KeyboardInput::isKeyToggled(int key)
    {
        glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
	    int state = glfwGetKey(window, key);
	    if(state == GLFW_PRESS)
	    	return true;
	    else
	    	return false;
    }

    SharedPtr<KeyboardInput> KeyboardInput::create(GLFWwindow* window)
    {
        return CreateShared<KeyboardInput>(window);
    }
}