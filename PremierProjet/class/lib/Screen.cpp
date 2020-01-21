#include <iostream>
using namespace std;

#include "../../class/header/Screen.h"
#include "../../class/header/Segment.h"
#include "../../class/header/Controller.h"

vector<Figure*> figureToDraw;

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

void Screen::Initialize() {
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		std::cout << "erreur d'initialisation de GLEW!"
			<< std::endl;
	}

	std::cout << "Version : " << glGetString(GL_VERSION) << std::endl;
	std::cout << "Vendor : " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer : " << glGetString(GL_RENDERER) << std::endl;
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