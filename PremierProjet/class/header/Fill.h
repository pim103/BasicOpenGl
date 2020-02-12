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

class Fill {
private:
public:
	void static ColorZone(GLFWwindow* window, double* coords);
	void static LCA(GLFWwindow* window, Polygon* poly);

	static vector<Point*> FindRectangleOfPoly(Polygon* poly);
};