#include "../../class/header/Controller.h"
#include "../../class/header/Screen.h"
#include "../../class/header/Polygon.h"

extern vector<Figure*> figureToDraw;
ControllerType controllerType;

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
			case ControllerType::DRAW_POLYGON:
				if (newPolygon != nullptr) {
					newPolygon->AddSegment(new Segment(newXa, newYa, x, y));
					newXa = x;
					newYa = y;
				}
				else {
					newPolygon = new Polygon();
					figureToDraw.push_back(newPolygon);
					newPolygon->AddSegment(new Segment(newXa, newYa, x, y));
					newXa = x;
					newYa = y;
				}
				break;
			case ControllerType::DRAW_SEGMENT:
				figureToDraw.push_back(new Segment(newXa, newYa, x, y));
				newXa = -2;
				newYa = -2;
				break;
			default:
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
		case GLFW_KEY_C:
			if (controllerType == ControllerType::DRAW_POLYGON) {
				cout << "Close Polygon" << endl;
				SwitchMode();
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
	default:
		break;
	}
}

void Controller::SetCallback(GLFWwindow* window) {
	glfwSetMouseButtonCallback(window, Controller::MouseButtonCallback);
	glfwSetKeyCallback(window, Controller::KeyboardCallback);
}