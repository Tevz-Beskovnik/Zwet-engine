#pragma once

#include<GL/glew.h>
#include<GLFW/glfw3.h>

namespace kbi {
		bool isKeyHeld(GLFWwindow* wind, int key);

		bool isKeyToggled(GLFWwindow* wind, int key);

		int cursorX();

		int cursorY();
};