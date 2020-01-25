#pragma once
#include "abstract/Figure.h";
#include "Point.h";
#include <vector>

class Segment: public Figure {
private:
	Point* firstPoint;
	Point* secondPoint;

	double normaleX;
	double normaleY;

	bool isWindowSegment;

	float red;
	float green;
	float blue;
public:
	Segment(float xA, float yA, float xB, float yB);
	Segment(Point *a, Point *b);
	Segment(Point* a, float xB, float yB);
	Segment(float xA, float yA, Point* b);

	void ClassicInit();

	Point* getFirstPoint();
	Point* getSecondPoint();
	float* GetColors();

	void SetColor(float r, float g, float b);
	void SetColor(float* colors);

	void DrawFigure();

	float* GetCoord();
	float* GetNormale();

	bool GetIsWindowSegment();
	void SetIsWindowSegment(bool toggle);
};