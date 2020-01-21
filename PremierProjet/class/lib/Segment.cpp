#include "../../class/header/Segment.h"
#include <vector>

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

void Segment::DrawFigure() {
	glVertexAttribPointer(0, 2, GL_FLOAT, false, 2 * sizeof(float), GetCoord());
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_LINES, 0, 2);
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