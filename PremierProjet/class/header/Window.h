#pragma once
#include "Polygon.h"

class Window: public Figure {
private:
	Polygon* polygon;
public:
	void SetPolygon(Polygon *nPolygon);
	void RemovePolygon();
	void DrawFigure();
};