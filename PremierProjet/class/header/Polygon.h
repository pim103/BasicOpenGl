#pragma once
#include <vector>

#include "Segment.h";
#include "abstract/Figure.h"

class Polygon: public Figure {
private:
	vector<Segment *> segments;
public:
	void AddSegment(Segment *seg);
	void DrawFigure();
	void ClosePolygon();

	bool CheckValidPolygon();

	vector<Segment*> GetSegments();
};