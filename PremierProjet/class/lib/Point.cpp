#include <iostream>
using namespace std;

#include "../../class/header/Point.h";
#include "../../class/header/Window.h";
#include "../../class/header/Utils.h";
#include "../../class/header/Screen.h";

extern vector<Window*> windows;
extern Screen* principalScreen;

Point::Point(float newX, float newY) {
	x = newX;
	y = newY;

	double* origCoords = Utils::ConverOpenGlToMouseClickCoord(principalScreen->getWindow(), x, y);
	origCoordX = origCoords[0];
	origCoordY = origCoords[1];

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
	double* coords = Utils::ConverOpenGlToMouseClickCoord(principalScreen->getWindow(), x, y);

	bool findWindowActive = false;
	for each (Window * window in windows)
	{
		if (window->CheckIfIsActive()) {
			findWindowActive = true;

			if (Utils::checkIfPointIsInPolygon(principalScreen->getWindow(), origCoordX, origCoordY, window->GetPolygon())) {
				findWindowActive = false;
				break;
			}
		}
	}
	
	if (!findWindowActive) {
		glBegin(GL_POINTS);
		glVertex2f(x, y);
		glEnd();
	}

	glColor3f(1.0, 1.0, 1.0);
}