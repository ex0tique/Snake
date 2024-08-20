#include "Application.h"

int main() {
	unsigned int screenWidth = 800;
	unsigned int windowHeight = 800;

	Application app(screenWidth, windowHeight);
	app.Run();

	return 0;
}