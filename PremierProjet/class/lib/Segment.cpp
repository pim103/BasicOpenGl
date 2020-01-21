#include "../../class/header/Segment.h"
#include <vector>

#include <math.h>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

Segment::Segment(float xA, float yA, float xB, float yB) {
	firstPoint = new Point(xA, yA);
	secondPoint = new Point(xB, yB);
}

Segment::Segment(Point* a, Point* b) {
	firstPoint = a;
	secondPoint = b;
}

Segment::Segment(Point* a, float xB, float yB) {
	firstPoint = a;
	secondPoint = new Point(xB, yB);
}

Segment::Segment(float xA, float yA, Point* b) {
	firstPoint = new Point(xA, yA);
	secondPoint = b;
}

void Segment::ClassicInit() {
	SetColor(1.0, 1.0, 1.0);

	float vecX = secondPoint->getX() - firstPoint->getX();
	float vecY = secondPoint->getY() - firstPoint->getY();

	double norm = sqrt(pow(vecX, 2) + pow(vecY, 2));
	double normX = vecX / norm;
	double normY = vecY / norm;

	normaleX = -normY;
	normaleY = normX;
}

float* Segment::GetColors() {
	float* colors = new float[3];
	colors[0] = red;
	colors[1] = green;
	colors[2] = blue;

	return colors;
}

void Segment::SetColor(float r, float g, float b) {
	red = r;
	green = g;
	blue = b;
}

void Segment::SetColor(float *colors) {
	red = colors[0];
	green = colors[1];
	blue = colors[2];
}

void Segment::DrawFigure() {
	glColor3f(red, green, blue);

	glVertexAttribPointer(0, 2, GL_FLOAT, false, 2 * sizeof(float), GetCoord());
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_LINES, 0, 2);

	glColor3f(1.0, 1.0, 1.0);
}

Point* Segment::getFirstPoint() {
	return firstPoint;
}

Point* Segment::getSecondPoint() {
	return secondPoint;
}

float* Segment::GetCoord() {
	float* coord = new float[4];
	coord[0] = firstPoint->getX();
	coord[1] = firstPoint->getY();
	coord[2] = secondPoint->getX();
	coord[3] = secondPoint->getY();

	return coord;
}