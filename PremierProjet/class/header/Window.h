#pragma once
#include "Polygon.h"

class Window: public Figure {
private:
	Polygon* polygon;
	bool isActive;
public:
	Window();
	void SetPolygon(Polygon *nPolygon);
	Polygon* GetPolygon();
	void RemovePolygon();
	void DrawFigure();
	bool CheckIfIsActive();
	void SetActive(bool toggle);

	vector<float*> Window::GetAllNormale();

	float* ApplyScreen(Segment *seg);
	void ApplyScreenShuterlandHodgman(Polygon* poly);
	void ApplyScreenShuterlandHodgman(Segment* seg);
};