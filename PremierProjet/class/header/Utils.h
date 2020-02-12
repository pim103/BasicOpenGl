#include "Polygon.h"

class Utils {
public:
	double static *ConvertMouseClickCoord(GLFWwindow* window, double x, double y);
	double static* ConverOpenGlToMouseClickCoord(GLFWwindow* window, double x, double y);

	static float* GetColorOfPixel(GLFWwindow* window, double x, double y);
	static bool checkIfAlreadyInPile(vector<double*> pile, double* coords);
	static bool checkIfPointIsInPolygon(GLFWwindow* window, double x, double y, float* color); 
	static bool Utils::checkIfPointIsInPolygon(GLFWwindow* window, double x, double y, Polygon* poly);

	static bool inside(Point* point1, Point* point2, Point* point, bool wasReversed);
	static Point* intersection(Point* point1, Point* point2, Point* point3, Point* point4);
	static bool checkIfIntersection(GLFWwindow* window, Point* point1, Point* point2, Point* point3, Point* point4);
	static vector<int> GetXOnLine(GLFWwindow* window, Polygon* poly, double xMin, double xMax, double y);

	static void DrawCircle(GLFWwindow* window, double x1, double y1, double x2, double y2);
};