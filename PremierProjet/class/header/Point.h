#pragma once
#include "abstract/Figure.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Point: public Figure {
private:
	float x;
	float y;

	float r;
	float g;
	float b;
public:
	Point(float newX, float newY);
	float getX();
	float getY();

	void SetColor(float* colors);

	void DrawFigure();
};