#include "pch.h"
#include "application.h"

int main()
{
	std::cout << "Starting..." << std::endl;

	if (glfwInit() == GLFW_TRUE)
	{
		Application app;
		app.run();

		glfwTerminate();
	}
}