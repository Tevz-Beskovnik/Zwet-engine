#include"kbInput.h"

bool kbi::isKeyHeld(GLFWwindow* activeWindow, int key) 
{
	glfwSetInputMode(activeWindow, GLFW_STICKY_KEYS, GLFW_FALSE);
	int state = glfwGetKey(activeWindow, key);
	if(state == GLFW_PRESS)
		return true;
	else
		return false;
}
bool kbi::isKeyToggled(GLFWwindow* activeWindow, int key) 
{
	glfwSetInputMode(activeWindow, GLFW_STICKY_KEYS, GLFW_TRUE);
	int state = glfwGetKey(activeWindow, key);
	if(state == GLFW_PRESS)
		return true;
	else
		return false;
}

int kbi::cursorX()
{
	;
}

int kbi::cursorY()
{
	;
}