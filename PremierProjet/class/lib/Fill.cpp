#include "../../class/header/Screen.h"
#include "../../class/header/Utils.h"
#include "../../class/header/Fill.h"

extern vector<Figure*> figureToDraw;
extern Screen* principalScreen;

void Fill::ColorZone(GLFWwindow* window, double* coords) {
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

		if ((currentPixel[0] != polygonColor[0] || currentPixel[1] != polygonColor[1] || currentPixel[2] != polygonColor[2]) &&
			(currentPixel[0] != fillColor[0] || currentPixel[1] != fillColor[1] || currentPixel[2] != fillColor[2])) {
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
				double* newCoords = new double[2];
				newCoords[0] = x;
				newCoords[1] = y - 1;

				if (!Utils::checkIfAlreadyInPile(pile, newCoords)) {
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

				if (!Utils::checkIfAlreadyInPile(pile, newCoords)) {
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

				if (!Utils::checkIfAlreadyInPile(pile, newCoords)) {
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

				if (!Utils::checkIfAlreadyInPile(pile, newCoords)) {
					pile.push_back(newCoords);
				}
			}
		}

		principalScreen->Display();
		glfwSwapBuffers(window);
	}
}

vector<Point*> Fill::FindRectangleOfPoly(Polygon* poly) {
	vector<Point*> coords;
	vector<Point*> allPoint = poly->GetAllPoint();

	float xMin = 10;
	float yMin = 10;
	float xMax = -10;
	float yMax = -10;

	float currentX;
	float currentY;

	for each (Point* point in allPoint)
	{
		currentX = point->getX();
		currentY = point->getY();

		if (currentX > xMax) {
			xMax = currentX;
		}

		if (currentX < xMin) {
			xMin = currentX;
		}

		if (currentY > yMax) {
			yMax = currentY;
		}

		if (currentY < yMin) {
			yMin = currentY;
		}
	}

	coords.push_back(new Point(xMin, yMin));
	coords.push_back(new Point(xMax, yMax));

	return coords;
}

void Fill::LCA(GLFWwindow* window, Polygon* poly) {
	poly->SetIsFill(true);

	vector<Point*> rectPoint = Fill::FindRectangleOfPoly(poly);
	vector<Point*> polyPoints = poly->GetAllPoint();

	double* minRect = Utils::ConverOpenGlToMouseClickCoord(window, rectPoint[0]->getX(), rectPoint[0]->getY());
	double* maxRect = Utils::ConverOpenGlToMouseClickCoord(window, rectPoint[1]->getX(), rectPoint[1]->getY());
	double* coords;

	float* fillColor = new float[3];
	fillColor[0] = 1;
	fillColor[1] = 0;
	fillColor[2] = 1;

	vector<int> intersectX;

	int nbIntersect;
	int count;
	float x;
	int tempX;
	int limitX;

	for (int i = maxRect[1] - 1; i < minRect[1] + 1; i++) {
		intersectX = Utils::GetXOnLine(window, poly, minRect[0] - 1, maxRect[0] + 1, i);
		nbIntersect = intersectX.size();
		count = 0;

		while (count < nbIntersect) {
			x = intersectX[count];
			count++;

			if (count == nbIntersect) {
				break;
			}

			limitX = intersectX[count];
			if (limitX < x) {
				tempX = x;
				x = limitX;
				limitX = tempX;
			}
			
			for (int j = x; j < limitX; j++) {
				coords = Utils::ConvertMouseClickCoord(window, j, i);
				Point* p = new Point(coords[0], coords[1]);
				p->SetColor(fillColor);

				figureToDraw.push_back(p);
			}
			count++;
		}
	}
}