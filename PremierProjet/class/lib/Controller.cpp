#include "../../class/header/Controller.h"
#include "../../class/header/Screen.h"
#include "../../class/header/Polygon.h"
#include "../../class/header/Window.h"

extern vector<Figure*> figureToDraw;
ControllerType controllerType;

extern Window* windowAlgo;
Polygon* newPolygon = nullptr;

float newXa = -2;
float newYa = -2;

Controller::Controller() {
	controllerType = ControllerType::DRAW_SEGMENT;
}

void Controller::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	double x = 0;
	double y = 0;
	int height = 0;
	int width = 0;

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		glfwGetWindowSize(window, &width, &height);
		glfwGetCursorPos(window, &x, &y);
		x = (x / width) * 2 - 1;
		y = ((y / height) * 2 - 1) * -1;

		if (newXa == -2) {
			newXa = x;
			newYa = y;
		}
		else {
			switch (controllerType)
			{
			case ControllerType::DRAW_WINDOW:
			case ControllerType::DRAW_POLYGON:
				if (newPolygon != nullptr) {
					Segment* newSeg = new Segment(newXa, newYa, x, y);
					if (controllerType == ControllerType::DRAW_WINDOW) {
						newSeg->SetColor(0.0, 0.0, 1.0);
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
					}
					else if (controllerType == ControllerType::DRAW_WINDOW) {
						windowAlgo->SetPolygon(newPolygon);
					}

					Segment* newSeg = new Segment(newXa, newYa, x, y);
					if (controllerType == ControllerType::DRAW_WINDOW) {
						newSeg->SetColor(0.0, 0.0, 1.0);
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
				Segment* newSeg = new Segment(newXa, newYa, x, y);
				newSeg->SetColor(1.0, 0.0, 0.0);

				figureToDraw.push_back(newSeg);
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
		case GLFW_KEY_F:
			cout << "Window mode" << endl;
			SwitchMode();
			controllerType = ControllerType::DRAW_WINDOW;
			break;
		case GLFW_KEY_C:
			cout << "Close Polygon" << endl;
			SwitchMode();
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
			if (!newPolygon->CheckValidPolygon()) {
				windowAlgo->RemovePolygon();
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