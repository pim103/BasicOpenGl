#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
using namespace std;

#include <vector>
#include <algorithm>
#include "abstract/Figure.h";
#include "Point.h";

class Utils {
public:
	double static *ConvertMouseClickCoord(GLFWwindow* window, double x, double y);
	float static* GetColorOfPixel(GLFWwindow* window, double x, double y);

	void static ColorZone(GLFWwindow* window, double* coords);
};