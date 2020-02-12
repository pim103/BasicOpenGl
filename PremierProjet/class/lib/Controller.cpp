#include "../../class/header/Controller.h"
#include "../../class/header/Screen.h"
#include "../../class/header/Polygon.h"
#include "../../class/header/Window.h"
#include "../../class/header/Utils.h"
#include "../../class/header/Fill.h"

extern vector<Figure*> figureToDraw;
ControllerType controllerType;

extern vector<Window*> windows;
Polygon* newPolygon = nullptr;

extern vector<Polygon*> polygon;

float newXa = -2;
float newYa = -2;

bool currentStateOfWindow = false;

Controller::Controller() {
	controllerType = ControllerType::DRAW_SEGMENT;
}

void Controller::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	double x = 0;
	double y = 0;
	double* newCoord;
	double* origCoord = new double[2];
	Segment* newSeg;

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		glfwGetCursorPos(window, &x, &y);

		origCoord[0] = x;
		origCoord[1] = y;

		newCoord = Utils::ConvertMouseClickCoord(window, x, y);

		x = newCoord[0];
		y = newCoord[1];

		if (controllerType == ControllerType::COLOR_ZONE) {
			float* polyColor = new float[3];
			polyColor[0] = 0;
			polyColor[1] = 1;
			polyColor[2] = 0;

			for each (Polygon * poly in polygon)
			{
				if (Utils::checkIfPointIsInPolygon(window, origCoord[0], origCoord[1], poly)) {
					if (!poly->GetIsFill()) {
						Fill::LCA(window, poly);
					}
				}
			}
			/*if (Utils::checkIfPointIsInPolygon(window, origCoord[0], origCoord[1], polyColor)) {
				Fill::ColorZone(window, origCoord);
			}*/
		}
		else if (newXa == -2) {
			newXa = x;
			newYa = y;
		}
		else {
			switch (controllerType)
			{
			case ControllerType::DRAW_WINDOW:
			case ControllerType::DRAW_POLYGON:
				if (newPolygon != nullptr) {
					newSeg = new Segment(newXa, newYa, x, y);
					if (controllerType == ControllerType::DRAW_WINDOW) {
						newSeg->SetColor(0.0, 0.0, 1.0);
						newSeg->SetIsWindowSegment(true);
					}
					else if (controllerType == ControllerType::DRAW_POLYGON) {
						newSeg->SetColor(0.0, 1.0, 0.0);
					}

					newPolygon->AddSegment(newSeg);
					newXa = x;
					newYa = y;
				}
				else {
					newPolygon = new Polygon();
					if (controllerType == ControllerType::DRAW_POLYGON) {
						figureToDraw.push_back(newPolygon);
						polygon.push_back(newPolygon);
					}
					else if (controllerType == ControllerType::DRAW_WINDOW) {
						figureToDraw.push_back(newPolygon);
					}

					newSeg = new Segment(newXa, newYa, x, y);
					if (controllerType == ControllerType::DRAW_WINDOW) {
						newSeg->SetColor(0.0, 0.0, 1.0);
						newSeg->SetIsWindowSegment(true);
					}
					else if (controllerType == ControllerType::DRAW_POLYGON) {
						newSeg->SetColor(0.0, 1.0, 0.0);
					}

					newPolygon->AddSegment(newSeg);
					newXa = x;
					newYa = y;
				}
				break;
			case ControllerType::DRAW_SEGMENT:
				newSeg = new Segment(newXa, newYa, x, y);
				newSeg->SetColor(1.0, 0.0, 0.0);

				figureToDraw.push_back(newSeg);
				newXa = -2;
				newYa = -2;
				break;
			case ControllerType::DRAW_CIRCLE:
				Utils::DrawCircle(window, x, y, newXa, newYa);
				newXa = -2;
				newYa = -2;
				break;
			}
		}
	}
}

void Controller::KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		switch (key)
		{
		case GLFW_KEY_P:
			cout << "Polygon mode" << endl;
			SwitchMode();
			controllerType = ControllerType::DRAW_POLYGON;
			break;
		case GLFW_KEY_S:
			cout << "Segment mode" << endl;
			SwitchMode();
			controllerType = ControllerType::DRAW_SEGMENT;
			break;
		case GLFW_KEY_W:
			cout << "Window mode" << endl;
			SwitchMode();
			controllerType = ControllerType::DRAW_WINDOW;
			break;
		case GLFW_KEY_E:
			cout << "End Polygon" << endl;
			SwitchMode();
			break;
		case GLFW_KEY_F:
			cout << "Paint Mode" << endl;
			SwitchMode();
			controllerType = ControllerType::COLOR_ZONE;
			break;
		case GLFW_KEY_R:
			cout << "RESET" << endl;
			controllerType = ControllerType::DRAW_SEGMENT;
			figureToDraw.clear();
			windows.clear();
			polygon.clear();
		case GLFW_KEY_C:
			cout << "Circle Mode" << endl;
			SwitchMode();
			controllerType = ControllerType::DRAW_CIRCLE;
			break;
		case GLFW_KEY_T:
			currentStateOfWindow = !currentStateOfWindow;
			for each (Window* window in windows)
			{
				window->SetActive(currentStateOfWindow);
			}
			break;
		default:
			break;
		}
	}
}

void Controller::SwitchMode() {
	switch (controllerType)
	{
	case ControllerType::DRAW_POLYGON:
		if (newPolygon != nullptr) {
			newPolygon->ClosePolygon();
			newPolygon->CheckValidPolygon();
		}
		newXa = -2;
		newYa = -2;
		newPolygon = nullptr;
		break;
	case ControllerType::DRAW_WINDOW:
		if (newPolygon != nullptr) {
			newPolygon->ClosePolygon();
			if (newPolygon->CheckValidPolygon()) {
				figureToDraw.pop_back();
				Window* newWindow = new Window();
				newWindow->SetPolygon(newPolygon);
				newWindow->SetActive(currentStateOfWindow);

				windows.push_back(newWindow);
				figureToDraw.push_back(newWindow);
			}
		}

		newXa = -2;
		newYa = -2;
		newPolygon = nullptr;
		break;
	default:
		break;
	}
}

void Controller::SetCallback(GLFWwindow* window) {
	glfwSetMouseButtonCallback(window, Controller::MouseButtonCallback);
	glfwSetKeyCallback(window, Controller::KeyboardCallback);
}