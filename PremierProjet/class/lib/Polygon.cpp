#include "../../class/header/Polygon.h"
#include "../../class/header/Screen.h"
#include "../../class/header/Window.h"

extern vector<Window*> windows;

Polygon::Polygon() {
	type = TypeFigure::POLYGON;
}

void Polygon::AddSegment(Segment* seg) {
	segments.push_back(seg);
}

void Polygon::DrawFigure() {
	bool findWindowActive = false;

	if (!GetIsWindowPoly()) {
		for each (Window * window in windows)
		{
			if (window->CheckIfIsActive()) {
				findWindowActive = true;
				window->ApplyScreenShuterlandHodgman(this);
			}
		}
	}

	if (!findWindowActive) {
		for each (Segment * seg in segments)
		{
			seg->DrawFigure();
		}
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

vector<Point*> Polygon::GetAllPoint() {
	vector<Point*> allPoints;
	vector<Segment*> polySegs = GetSegments();

	for (int i = 0; i < polySegs.size() - 1; i++) {
		if (i == 0) {
			allPoints.push_back(polySegs[i]->getFirstPoint());
			allPoints.push_back(polySegs[i]->getSecondPoint());
		}
		else {
			allPoints.push_back(polySegs[i]->getSecondPoint());
		}
	}

	return allPoints;
}


bool Polygon::GetIsWindowPoly() {
	return isWindow;
}

void Polygon::SetIsWindowPoly(bool toggle) {
	isWindow = toggle;
}

float* Polygon::GetColor() {
	return segments[0]->GetColors();
}

Polygon* Polygon::getPoly() {
	return this;
}

bool Polygon::GetIsFill() {
	return isFill;
}

void Polygon::SetIsFill(bool toggle) {
	isFill = toggle;
}