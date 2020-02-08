#include <iostream>
using namespace std;

#include "../header/Screen.h"
#include "../header/Segment.h"
#include "../header/Controller.h"
#include "../header/Window.h"

#include "../header/Utils.h"

vector<Figure*> figureToDraw;
Window* windowAlgo;

extern Screen* principalScreen;

Screen::Screen(int width, int height, string windowTitle) {
	/* Initialize the library */
	if (!glfwInit()) {
		exit(-1);
	}

	window = glfwCreateWindow(width, height, windowTitle.data(), NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(window);
}

GLFWwindow* Screen::getWindow() {
	return window;
}

void Screen::Initialize() {
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		std::cout << "erreur d'initialisation de GLEW!"
			<< std::endl;
	}
	/*
	Polygon* poly = new Polygon();
	
	Segment* seg = new Segment(0.7, 0.7, -0.7, 0.7);
	seg->SetIsWindowSegment(true);
	seg->SetColor(0.0, 1.0, 1.0);
	poly->AddSegment(seg);

	seg = new Segment(-0.7, 0.7, -0.7, -0.7);
	seg->SetIsWindowSegment(true);
	seg->SetColor(0.0, 1.0, 1.0);
	poly->AddSegment(seg);

	seg = new Segment(-0.7, -0.7, 0.7, -0.7);
	seg->SetIsWindowSegment(true);
	seg->SetColor(0.0, 1.0, 1.0);
	poly->AddSegment(seg);

	poly->ClosePolygon();
	*/
	//figureToDraw.push_back(new Segment(0.5, 0.5, -0.5, -0.5));
	/*
	double* coords = Utils::ConvertMouseClickCoord(window, 50, 150);
	double* coords2 = Utils::ConvertMouseClickCoord(window, 200, 50);
	Polygon * poly = new Polygon();
	Segment * seg = new Segment(coords[0], coords[1], coords2[0], coords2[1]);
	seg->SetColor(1.0, 0.0, 1.0);
	poly->AddSegment(seg);

	double* coords3 = Utils::ConvertMouseClickCoord(window, 350, 150);
	seg = new Segment(coords2[0], coords2[1], coords3[0], coords3[1]);
	seg->SetColor(1.0, 0.0, 1.0);
	poly->AddSegment(seg);

	double* coords4 = Utils::ConvertMouseClickCoord(window, 350, 300);
	seg = new Segment(coords3[0], coords3[1], coords4[0], coords4[1]);
	seg->SetColor(1.0, 0.0, 1.0);
	poly->AddSegment(seg);

	double* coords5 = Utils::ConvertMouseClickCoord(window, 250, 300);
	seg = new Segment(coords4[0], coords4[1], coords5[0], coords5[1]);
	seg->SetColor(1.0, 0.0, 1.0);
	poly->AddSegment(seg);

	double* coords6 = Utils::ConvertMouseClickCoord(window, 200, 250);
	seg = new Segment(coords5[0], coords5[1], coords6[0], coords6[1]);
	seg->SetColor(1.0, 0.0, 1.0);
	poly->AddSegment(seg);

	double* coords7 = Utils::ConvertMouseClickCoord(window, 150, 350);
	seg = new Segment(coords6[0], coords6[1], coords7[0], coords7[1]);
	seg->SetColor(1.0, 0.0, 1.0);
	poly->AddSegment(seg);

	double* coords8 = Utils::ConvertMouseClickCoord(window, 100, 250);
	seg = new Segment(coords7[0], coords7[1], coords8[0], coords8[1]);
	seg->SetColor(1.0, 0.0, 1.0);
	poly->AddSegment(seg);

	double* coords9 = Utils::ConvertMouseClickCoord(window, 100, 200);
	seg = new Segment(coords8[0], coords8[1], coords9[0], coords9[1]);
	seg->SetColor(1.0, 0.0, 1.0);
	poly->AddSegment(seg);

	poly->ClosePolygon();

	figureToDraw.push_back(poly);
	*/
	windowAlgo = new Window();
	figureToDraw.push_back(windowAlgo);
	/*
	poly = new Polygon();
	coords = Utils::ConvertMouseClickCoord(window, 100, 100);
	coords2 = Utils::ConvertMouseClickCoord(window, 300, 100);
	seg = new Segment(coords[0], coords[1], coords2[0], coords2[1]);
	seg->SetColor(0.0, 1.0, 1.0);
	poly->AddSegment(seg);

	coords3 = Utils::ConvertMouseClickCoord(window, 300, 300);
	seg = new Segment(coords2[0], coords2[1], coords3[0], coords3[1]);
	seg->SetColor(0.0, 1.0, 1.0);
	poly->AddSegment(seg);

	coords4 = Utils::ConvertMouseClickCoord(window, 100, 300);
	seg = new Segment(coords3[0], coords3[1], coords4[0], coords4[1]);
	seg->SetColor(0.0, 1.0, 1.0);
	poly->AddSegment(seg);

	poly->ClosePolygon();
	
	windowAlgo->SetPolygon(poly);
	windowAlgo->SetActive(true);
	*/
	//std::cout << "Version : " << glGetString(GL_VERSION) << std::endl;
	//std::cout << "Vendor : " << glGetString(GL_VENDOR) << std::endl;
	//std::cout << "Renderer : " << glGetString(GL_RENDERER) << std::endl;
}

void Screen::Display() {
	int width, height;
	glfwGetWindowSize(window, &width, &height);

	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	// Desactive le "scissoring"
	glDisable(GL_SCISSOR_TEST);
	// Defini le viewport en pleine fenetre
	glViewport(0, 0, width, height);

	for each (Figure * figure in figureToDraw)
	{
		figure->DrawFigure();
	}
}

void Screen::Shutdown() {

}

void Screen::InitializeAndLaunch() {
	// toutes nos initialisations vont ici
	Initialize();
	
	Controller *controller = new Controller();
	controller->SetCallback(window);
	
	/*
	Polygon* poly = new Polygon();
	
	Segment* seg = new Segment(0.7, 0.7, -0.7, 0.7);
	seg->SetIsWindowSegment(true);
	seg->SetColor(0.0, 1.0, 1.0);
	poly->AddSegment(seg);
	
	seg = new Segment(-0.7, 0.7, -0.7, -0.7);
	seg->SetIsWindowSegment(true);
	seg->SetColor(0.0, 1.0, 1.0);
	poly->AddSegment(seg);

	seg = new Segment(-0.7, -0.7, 0.7, -0.7);
	seg->SetIsWindowSegment(true);
	seg->SetColor(0.0, 1.0, 1.0);
	poly->AddSegment(seg);

	poly->ClosePolygon();

	windowAlgo->SetPolygon(poly);
	windowAlgo->SetActive(true);
	//figureToDraw.push_back(new Segment(0.5, 0.5, -0.5, -0.5));

	poly = new Polygon();
	seg = new Segment(-0.8, 0.8, 0.8, -0.8);
	seg->SetColor(1.0, 0.0, 1.0);
	poly->AddSegment(seg);

	seg = new Segment(0.8, -0.8, 0.6, 0.6);
	seg->SetColor(1.0, 0.0, 1.0);
	poly->AddSegment(seg);

	poly->ClosePolygon();

	figureToDraw.push_back(poly);*/

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		Display();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	// ne pas oublier de liberer la memoire etc...
	Shutdown();

	glfwTerminate();
}
/*
int main(int argc, char** argv)
{
	// subject polygon
	point2D subjectPolygon[] = {
		{50,150}, {200,50}, {350,150},
		{350,300},{250,300},{200,250},
		{150,350},{100,250},{100,200}
	};
	int subjectPolygonSize = sizeof(subjectPolygon) / sizeof(subjectPolygon[0]);

	// clipping polygon
	point2D clipPolygon[] = { {100,100}, {300,100}, {300,300}, {100,300} };
	int clipPolygonSize = sizeof(clipPolygon) / sizeof(clipPolygon[0]);

	// define the new clipped polygon (empty)
	int newPolygonSize = 0;
	point2D newPolygon[N] = { 0 };

	// apply clipping
	SutherlandHodgman(subjectPolygon, subjectPolygonSize, clipPolygon, clipPolygonSize, newPolygon, newPolygonSize);

	principalScreen = new Screen(640, 480, "Hello World");

	principalScreen->InitializeAndLaunch();

	// print clipped polygon points
	/*cout << "Clipped polygon points:" << endl;
	double* coords = new double[2];
	coords[0] = 1;
	coords[1] = 2;
	for (int i = 0; i < newPolygonSize; i++) {
		cout << "(" << newPolygon[i].x << ", " << newPolygon[i].y << ")" << endl;
		coords = Utils::ConvertMouseClickCoord(principalScreen->getWindow(), newPolygon[i].x, newPolygon[i].y);
		cout << "(" << coords[0] << ", " << coords[1] << ")" << endl;
	}*/
/*	return 0;
}*/