#pragma once
#include <iostream>
using namespace std;

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include "abstract/Figure.h";
#include "Segment.h";

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