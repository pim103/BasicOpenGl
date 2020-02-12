#include "../../class/header/Screen.h"
#include "../../class/header/Utils.h"

extern vector<Figure*> figureToDraw;

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

bool Utils::checkIfAlreadyInPile(vector<double*> pile, double* coords) {
	for each (double* coordsInPile in pile)
	{
		if (coordsInPile[0] == coords[0] && coordsInPile[1] == coords[1]) {
			return true;
		}
	}

	return false;
}

bool Utils::checkIfPointIsInPolygon(GLFWwindow* window, double x, double y, float* color) {
	int width, height;

	float* currentPixel;

	glfwGetWindowSize(window, &width, &height);

	float* lastColor = nullptr;
	int nbIntersection = 0;

	while (x < width) {
		currentPixel = Utils::GetColorOfPixel(window, x, y);

		if (currentPixel[0] == color[0] && currentPixel[1] == color[1] && currentPixel[2] == color[2]) {
			if (lastColor != nullptr && (lastColor[0] != currentPixel[0] || lastColor[1] != currentPixel[1] || lastColor[2] != currentPixel[2])) {
				nbIntersection++;
			}
		}

		x++;
		lastColor = currentPixel;
	}

	return (nbIntersection % 2 == 1);
}

Point* Utils::intersection(Point* point1, Point* point2, Point* point3, Point* point4)
{
	float x1 = point1->getX();
	float y1 = point1->getY();
	float x2 = point2->getX();
	float y2 = point2->getY();
	float x3 = point3->getX();
	float y3 = point3->getY();
	float x4 = point4->getX();
	float y4 = point4->getY();

	float* dc = new float[2];
	float* dp = new float[2];

	dc[0] = x1 - x2;
	dc[1] = y1 - y2;

	dp[0] = x3 - x4;
	dp[1] = y3 - y4;

	float n1 = x1 * y2 - y1 * x2;
	float n2 = x3 * y4 - y3 * x4;
	float n3 = 1.0 / (dc[0] * dp[1] - dc[1] * dp[0]);

	Point * intersectionPoint = new Point((n1 * dp[0] - n2 * dc[0]) * n3, (n1 * dp[1] - n2 * dc[1]) * n3);
	return intersectionPoint;
}

bool Utils::inside(Point * point1, Point * point2, Point * point, bool wasReversed) {
	float x = point->getX();
	float y = point->getY();

	float x1 = point1->getX();
	float y1 = point1->getY();
	float x2 = point2->getX();
	float y2 = point2->getY();

	double* coords = new double[2];
	coords = Utils::ConverOpenGlToMouseClickCoord(nullptr, x, y);

	double* coords1 = new double[2];
	coords1 = Utils::ConverOpenGlToMouseClickCoord(nullptr, x1, y1);

	double* coords2 = new double[2];
	coords2 = Utils::ConverOpenGlToMouseClickCoord(nullptr, x2, y2);

	//double val = (coords2[1] - coords1[1]) * coords[0] + (coords1[0] - coords2[0]) * coords[1] + (coords2[0] * coords1[1] - coords1[0] * coords2[1]);
	double val = (y2 - y1) * x + (x1 - x2) * y + (x2 * y1 - x1 * y2);

	if (wasReversed) {
		return val > 0;
	}
	else {
		return val < 0;
	}
}

bool Utils::checkIfIntersection(GLFWwindow* window, Point* point1, Point* point2, Point* point3, Point* point4) {
	float x1 = point1->getX();
	float y1 = point1->getY();
	float x2 = point2->getX();
	float y2 = point2->getY();

	double* coords = Utils::ConverOpenGlToMouseClickCoord(window, point3->getX(), point3->getY());
	float x3 = coords[0];
	float y3 = coords[1];
	
	coords = Utils::ConverOpenGlToMouseClickCoord(window, point4->getX(), point4->getY());
	float x4 = coords[0];
	float y4 = coords[1];
	
	float* dc = new float[2];
	float* dp = new float[2];

	dc[0] = x1 - x2;
	dc[1] = y1 - y2;

	dp[0] = x3 - x4;
	dp[1] = y3 - y4;

	float n1 = x1 * y2 - y1 * x2;
	float n2 = x3 * y4 - y3 * x4;
	float n3 = 1.0 / (dc[0] * dp[1] - dc[1] * dp[0]);

	float commonX = (n1 * dp[0] - n2 * dc[0]) * n3;
	float commonY = (n1 * dp[1] - n2 * dc[1]) * n3;

	if ((commonX >= x1 && commonX <= x2 || commonX >= x2 && commonX <= x1) &&
		(commonX >= x3 && commonX <= x4 || commonX >= x4 && commonX <= x3) &&
		(commonY >= y1 && commonY <= y2 || commonY >= y2 && commonY <= y1) &&
		(commonY >= y3 && commonY <= y4 || commonY >= y4 && commonY <= y3)
		) {
		return true;
	}

	return false;
}

bool Utils::checkIfPointIsInPolygon(GLFWwindow* window, double x, double y, Polygon* poly) {
	Point* point1 = new Point(x, y);
	Point* point2 = new Point(640, y + 1);

	vector<Point*> polyPoints = poly->GetAllPoint();

	int polySize = polyPoints.size();
	int nbIntersection = 0;

	for (int i = 0; i < polySize; i++) {
		if (Utils::checkIfIntersection(window, point1, point2, polyPoints[i], polyPoints[(i + 1) % polySize])) {
			nbIntersection++;
		}
	}

	return (nbIntersection % 2) == 1;
}

vector<int> Utils::GetXOnLine(GLFWwindow* window, Polygon* poly, double xMin, double xMax, double y) {
	float* dc = new float[2];
	float* dp = new float[2];

	dc[0] = xMin - xMax;
	dc[1] = y - y;

	vector<Point*> polyPoints = poly->GetAllPoint();
	int size = polyPoints.size();

	vector<int> result;

	for (int i = 0; i < size; i++) {
		Point* point3 = polyPoints[i];
		Point* point4 = polyPoints[(i + 1) % size];

		double* coords = Utils::ConverOpenGlToMouseClickCoord(window, point3->getX(), point3->getY());
		float x3 = coords[0];
		float y3 = coords[1];

		coords = Utils::ConverOpenGlToMouseClickCoord(window, point4->getX(), point4->getY());
		float x4 = coords[0];
		float y4 = coords[1];

		dp[0] = x3 - x4;
		dp[1] = y3 - y4;

		float n1 = xMin * y - y * xMax;
		float n2 = x3 * y4 - y3 * x4;
		float n3 = 1.0 / (dc[0] * dp[1] - dc[1] * dp[0]);

		float commonX = (n1 * dp[0] - n2 * dc[0]) * n3;
		float commonY = (n1 * dp[1] - n2 * dc[1]) * n3;

		if ((commonX >= xMin && commonX <= xMax || commonX >= xMax && commonX <= xMin) &&
			(commonX >= x3 && commonX <= x4 || commonX >= x4 && commonX <= x3))
		{
			result.push_back(commonX);
		}
	}

	return result;
}


void Utils::DrawCircle(GLFWwindow* window, double x1, double y1, double x2, double y2) {
	double* centerOrig = Utils::ConverOpenGlToMouseClickCoord(window, x1, y1);
	double* pointOnCircle = Utils::ConverOpenGlToMouseClickCoord(window, x2, y2);

	x2 = centerOrig[0];
	y2 = centerOrig[1];
	x1 = pointOnCircle[0];
	y1 = pointOnCircle[1];

	int rayon = sqrt(pow((y2 - y1), 2) + pow((x2 - x1), 2));

	float* color = new float[3];
	color[0] = 0.0;
	color[0] = 1.0;
	color[0] = 1.0;

	int x = 0;
	int y = rayon;
	int m = 5 - (4 * rayon);
	Point* newPoint;
	double* coords;

	while (x <= y) {
		coords = Utils::ConvertMouseClickCoord(window, x + x1, y + y1);
		newPoint = new Point(coords[0], coords[1]);
		newPoint->SetColor(color);
		figureToDraw.push_back(newPoint);

		coords = Utils::ConvertMouseClickCoord(window, y + x1, x + y1);
		newPoint = new Point(coords[0], coords[1]);
		newPoint->SetColor(color);
		figureToDraw.push_back(newPoint);

		coords = Utils::ConvertMouseClickCoord(window, -x + x1, y + y1);
		newPoint = new Point(coords[0], coords[1]);
		newPoint->SetColor(color);
		figureToDraw.push_back(newPoint);

		coords = Utils::ConvertMouseClickCoord(window, -y + x1, x + y1);
		newPoint = new Point(coords[0], coords[1]);
		newPoint->SetColor(color);
		figureToDraw.push_back(newPoint);

		coords = Utils::ConvertMouseClickCoord(window, x + x1, -y + y1);
		newPoint = new Point(coords[0], coords[1]);
		newPoint->SetColor(color);
		figureToDraw.push_back(newPoint);

		coords = Utils::ConvertMouseClickCoord(window, y + x1, -x + y1);
		newPoint = new Point(coords[0], coords[1]);
		newPoint->SetColor(color);
		figureToDraw.push_back(newPoint);

		coords = Utils::ConvertMouseClickCoord(window, -x + x1, -y + y1);
		newPoint = new Point(coords[0], coords[1]);
		newPoint->SetColor(color);
		figureToDraw.push_back(newPoint);

		coords = Utils::ConvertMouseClickCoord(window, -y + x1, -x + y1);
		newPoint = new Point(coords[0], coords[1]);
		newPoint->SetColor(color);
		figureToDraw.push_back(newPoint);

		if (m > 0) {
			y--;
			m -= (8 * y);
		}

		x++;
		m += (8 * x) + 4;
	}
}