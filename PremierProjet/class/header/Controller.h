#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

enum ControllerType {
	DRAW_SEGMENT,
	DRAW_POLYGON,
	DRAW_WINDOW,
	COLOR_ZONE,
	DRAW_CIRCLE
};

class Controller {
private:
public:
	Controller();

	static void SwitchMode();
	void SetCallback(GLFWwindow* window);
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};