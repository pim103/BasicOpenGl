#pragma once
#include <vector>

#include "Segment.h";
#include "abstract/Figure.h"

class Polygon: public Figure {
private:
	vector<Segment *> segments;
	bool isWindow;
	bool isFill;
public:
	Polygon();

	void AddSegment(Segment *seg);
	void DrawFigure();
	void ClosePolygon();

	bool CheckValidPolygon();
	vector<Point*> Polygon::GetAllPoint();

	vector<Segment*> GetSegments();

	float* GetColor();
	bool GetIsWindowPoly();
	void SetIsWindowPoly(bool toggle);

	bool GetIsFill();
	void SetIsFill(bool toggle);

	Polygon* getPoly();
};