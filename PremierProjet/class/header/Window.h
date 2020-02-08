#pragma once
#include "Polygon.h"

bool inside(Point* point1, Point* point2, Point* point);
Point* intersection(Point* point1, Point* point2, Point* point3, Point* point4);

class Window: public Figure {
private:
	Polygon* polygon;
	bool isActive;
public:
	Window();
	void SetPolygon(Polygon *nPolygon);
	void RemovePolygon();
	void DrawFigure();
	bool CheckIfIsActive();
	void SetActive(bool toggle);

	vector<float*> Window::GetAllNormale();

	float* ApplyScreen(Segment *seg);
	void ApplyScreenShuterlandHodgman(Polygon* poly);
};