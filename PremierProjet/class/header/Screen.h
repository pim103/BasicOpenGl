#pragma once
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
using namespace std;

class Screen {
private:
	GLFWwindow* window;
public:
	Screen(int width, int height, string windowTitle);
	
	void Initialize();
	void Display();
	void Shutdown();

	void InitializeAndLaunch();
};