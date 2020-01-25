//
//
//

// GLEW_STATIC force le linkage statique
// c-a-d que le code de glew est directement injecte dans l'executable
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// les repertoires d'includes sont:
// ../libs/glfw-3.3/include			fenetrage
// ../libs/glew-2.1.0/include		extensions OpenGL
// ../libs/stb						gestion des images (entre autre)

// les repertoires des libs sont (en 64-bit):
// ../libs/glfw-3.3/lib-vc2015
// ../libs/glew-2.1.0/lib/Release/x64

// Pensez a copier les dll dans le repertoire x64/Debug, cad:
// glfw-3.3/lib-vc2015/glfw3.dll
// glew-2.1.0/bin/Release/x64/glew32.dll		si pas GLEW_STATIC

// _WIN32 indique un programme Windows
// _MSC_VER indique la version du compilateur VC++
#if defined(_WIN32) && defined(_MSC_VER)
#pragma comment(lib, "glfw3dll.lib")
#pragma comment(lib, "glew32s.lib")			// glew32.lib si pas GLEW_STATIC
#pragma comment(lib, "opengl32.lib")
#elif defined(__APPLE__)
#elif defined(__linux__)
#endif

#include <iostream>

#include "class/header/Screen.h"

Screen* principalScreen;

int main(void)
{
	principalScreen = new Screen(640, 480, "Hello World");

	principalScreen->InitializeAndLaunch();

	return 0;
}