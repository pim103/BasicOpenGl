#pragma once
#include "abstract/Figure.h";
#include "Point.h";
#include <vector>

class Segment: public Figure {
private:
	Point* firstPoint;
	Point* secondPoint;
public:
	Point* getFirstPoint();
	Point* getSecondPoint();
	Segment(float xA, float yA, float xB, float yB);
	Segment(Point *a, Point *b);
	Segment(Point* a, float xB, float yB);
	Segment(float xA, float yA, Point* b);
	void DrawFigure();

	float* GetCoord();
};