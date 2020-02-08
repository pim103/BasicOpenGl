#include "../../class/header/Screen.h"
#include "../../class/header/Utils.h"

extern vector<Figure*> figureToDraw;
extern Screen* principalScreen;

double* Utils::ConvertMouseClickCoord(GLFWwindow *window, double x, double y) {
	int width, height;
	glfwGetWindowSize(window, &width, &height);

	width = 640;
	height = 480;
	x = (x / width) * 2 - 1;
	y = ((y / height) * 2 - 1) * -1;
	
	double* coords = new double[2];

	coords[0] = x;
	coords[1] = y;

	return coords;
}

double* Utils::ConverOpenGlToMouseClickCoord(GLFWwindow* window, double x, double y) {
	int width, height;
	//glfwGetWindowSize(window, &width, &height);

	width = 640;
	height = 480;
	x = ((x + 1) * width) / 2;
	y =  ((y * -1 + 1) / 2) * height;

	double* coords = new double[2];

	coords[0] = x;
	coords[1] = y;

	return coords;
}

float* Utils::GetColorOfPixel(GLFWwindow* window, double x, double y) {
	float* color = new float[3];
	int width, height;
	glfwGetWindowSize(window, &width, &height);

	unsigned int pixel;

	glReadPixels(x, height - y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &pixel);
	color[0] = (float)((pixel & 0x0000FF)) / 255;
	color[1] = (float)((pixel & 0x00FF00) >> 8) / 255;
	color[2] = (float)((pixel & 0xFF0000) >> 16) / 255;

	return color;
}

bool checkIfAlreadyInPile(vector<double*> pile, double* coords) {
	for each (double* coordsInPile in pile)
	{
		if (coordsInPile[0] == coords[0] && coordsInPile[1] == coords[1]) {
			return true;
		}
	}

	return false;
}

void Utils::ColorZone(GLFWwindow* window, double* coords) {
	float* polygonColor = new float[3];
	polygonColor[0] = 0;
	polygonColor[1] = 1;
	polygonColor[2] = 0;

	float* fillColor = new float[3];
	fillColor[0] = 1;
	fillColor[1] = 0;
	fillColor[2] = 1;

	float* segmentColor = new float[3];
	segmentColor[0] = 1;
	segmentColor[1] = 0;
	segmentColor[2] = 0;

	int width, height;
	glfwGetWindowSize(window, &width, &height);

	double x = coords[0];
	double y = coords[1];

	float* currentPixel;

	vector<double*> pile;
	vector<double*> alreadyParsed;
	pile.push_back(coords);

	while (size(pile) > 0) {
		x = pile[0][0];
		y = pile[0][1];
		pile.erase(pile.begin());

		/*double* ccoord = new double[2];
		ccoord[0] = x;
		ccoord[1] = y;
		alreadyParsed.push_back(ccoord);
		*/
		currentPixel = Utils::GetColorOfPixel(window, x, y);

		if ( (currentPixel[0] != polygonColor[0] || currentPixel[1] != polygonColor[1] || currentPixel[2] != polygonColor[2]) &&
			(currentPixel[0] != fillColor[0] || currentPixel[1] != fillColor[1] || currentPixel[2] != fillColor[2]) ) {
			double* newCoord = Utils::ConvertMouseClickCoord(window, x, y);
			Point* p = new Point(newCoord[0], newCoord[1]);
			p->SetColor(fillColor);

			figureToDraw.push_back(p);
		}

		if (y - 1 >= 0) {
			currentPixel = Utils::GetColorOfPixel(window, x, y - 1);
			if (!(currentPixel[0] == polygonColor[0] && currentPixel[1] == polygonColor[1] && currentPixel[2] == polygonColor[2]) &&
				!(currentPixel[0] == fillColor[0] && currentPixel[1] == fillColor[1] && currentPixel[2] == fillColor[2]) &&
				!(currentPixel[0] == segmentColor[0] && currentPixel[1] == segmentColor[1] && currentPixel[2] == segmentColor[2])) {
				double * newCoords = new double[2];
				newCoords[0] = x;
				newCoords[1] = y - 1;

				if (!checkIfAlreadyInPile(pile, newCoords)) {
					pile.push_back(newCoords);
				}
			}
		}

		if (x - 1 >= 0) {
			currentPixel = Utils::GetColorOfPixel(window, x - 1, y);
			if (!(currentPixel[0] == polygonColor[0] && currentPixel[1] == polygonColor[1] && currentPixel[2] == polygonColor[2]) &&
				!(currentPixel[0] == fillColor[0] && currentPixel[1] == fillColor[1] && currentPixel[2] == fillColor[2]) &&
				!(currentPixel[0] == segmentColor[0] && currentPixel[1] == segmentColor[1] && currentPixel[2] == segmentColor[2])) {
				double* newCoords = new double[2];
				newCoords[0] = x - 1;
				newCoords[1] = y;

				if (!checkIfAlreadyInPile(pile, newCoords)) {
					pile.push_back(newCoords);
				}
			}
		}

		if (y + 1 < height) {
			currentPixel = Utils::GetColorOfPixel(window, x, y + 1);
			if (!(currentPixel[0] == polygonColor[0] && currentPixel[1] == polygonColor[1] && currentPixel[2] == polygonColor[2]) &&
				!(currentPixel[0] == fillColor[0] && currentPixel[1] == fillColor[1] && currentPixel[2] == fillColor[2]) &&
				!(currentPixel[0] == segmentColor[0] && currentPixel[1] == segmentColor[1] && currentPixel[2] == segmentColor[2])) {
				double* newCoords = new double[2];
				newCoords[0] = x;
				newCoords[1] = y + 1;

				if (!checkIfAlreadyInPile(pile, newCoords)) {
					pile.push_back(newCoords);
				}
			}
		}

		if (x + 1 < width) {
			currentPixel = Utils::GetColorOfPixel(window, x + 1, y);
			if (!(currentPixel[0] == polygonColor[0] && currentPixel[1] == polygonColor[1] && currentPixel[2] == polygonColor[2]) &&
				!(currentPixel[0] == fillColor[0] && currentPixel[1] == fillColor[1] && currentPixel[2] == fillColor[2]) &&
				!(currentPixel[0] == segmentColor[0] && currentPixel[1] == segmentColor[1] && currentPixel[2] == segmentColor[2])) {
				double* newCoords = new double[2];
				newCoords[0] = x + 1;
				newCoords[1] = y;

				if (!checkIfAlreadyInPile(pile, newCoords)) {
					pile.push_back(newCoords);
				}
			}
		}

		principalScreen->Display();
		glfwSwapBuffers(window);
	}
}