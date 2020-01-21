#include "../../class/header/Screen.h"
#include "../../class/header/Window.h"

void Window::SetPolygon(Polygon* nPolygon) {
	polygon = nPolygon;
}

void Window::RemovePolygon() {
	polygon = nullptr;
}

void Window::DrawFigure() {
	if (polygon != nullptr) {
		polygon->DrawFigure();
	}
}