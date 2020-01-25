#include <iostream>
using namespace std;

#include "../../class/header/Point.h";

Point::Point(float newX, float newY) {
	x = newX;
	y = newY;

	r = 1.0;
	g = 1.0;
	b = 1.0;
}

float Point::getX() {
	return x;
}

float Point::getY() {
	return y;
}


void Point::SetColor(float* colors) {
	r = colors[0];
	g = colors[1];
	b = colors[2];
}

void Point::DrawFigure() {
	glColor3f(r, g, b);

	glBegin(GL_POINTS);
		glVertex2f(x, y);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
}