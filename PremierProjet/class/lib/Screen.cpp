#include <iostream>
using namespace std;

#include "../../class/header/Screen.h"

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

	glClearColor(1.f, 1.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	// Desactive le "scissoring"
	glDisable(GL_SCISSOR_TEST);
	// Defini le viewport en pleine fenetre
	glViewport(0, 0, width, height);

	// Idem mais en OpenGL moderne
	// defini une liste de sommets, 2D, de type float
	const float triangles[] = {
		-0.5f, -0.5f,
		-0.5f, +0.5f,
		+0.5f, +0.5f,
		// second triangle
		-0.5f, -0.5f,
		+0.5f, +0.5f,
		+0.5f, -0.5f
	};

	// Specifie la structure des donnees envoyees au GPU
	glVertexAttribPointer(0, 2, GL_FLOAT, false, 2 * sizeof(float), triangles);
	// indique que les donnees sont sous forme de tableau
	glEnableVertexAttribArray(0);
	// dessine deux triangles
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Screen::Shutdown() {

}

void Screen::InitializeAndLaunch() {
	// toutes nos initialisations vont ici
	Initialize();

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