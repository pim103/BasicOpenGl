#pragma once
#include "Polygon.h"

typedef struct segmentCode segmentCode;
struct segmentCode {
	int sum;
	int left;
	int right;
	int up;
	int down;
};

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

	vector<Point*> GetAllPoint();
	vector<float*> Window::GetAllNormale();

	float* ApplyScreen(Segment *seg);
};