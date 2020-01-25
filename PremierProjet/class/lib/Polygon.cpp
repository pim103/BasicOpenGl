#include "../../class/header/Polygon.h"
#include "../../class/header/Screen.h"

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
		Point* lastPoint = segments[(segmentsSize - 1)]->getSecondPoint();

		Segment * newSeg = new Segment(firstPoint, lastPoint);
		newSeg->SetColor(segments[0]->GetColors());
		newSeg->SetIsWindowSegment(segments[0]->GetIsWindowSegment());

		segments.push_back(newSeg);
	}
}

bool Polygon::CheckValidPolygon() {
	if (segments.size() > 2) {
		return true;
	}

	return false;
}


vector<Segment *> Polygon::GetSegments() {
	return segments;
}