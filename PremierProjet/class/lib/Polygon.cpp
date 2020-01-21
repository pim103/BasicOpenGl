#include "../../class/header/Polygon.h"

void Polygon::AddSegment(Segment* seg) {
	segments.push_back(seg);
}

void Polygon::DrawFigure() {
	for each (Segment* seg in segments)
	{
		seg->DrawFigure();
	}
}

void Polygon::ClosePolygon() {
	int segmentsSize = segments.size();

	if (segmentsSize != 0) {
		Point* firstPoint = segments[0]->getFirstPoint();
		Point* lastPoint = segments[segmentsSize - 1]->getSecondPoint();

		segments.push_back(new Segment(firstPoint, lastPoint));
	}
}

bool Polygon::CheckValidPolygon() {
	if (segments.size() > 2) {
		return true;
	}

	return false;
}