#include "pch.h"
#include "application.h"

int main()
{
	std::cout << "Launching PwAG Space Shooter Game..." << std::endl;

	if (glfwInit() == GLFW_TRUE)
	{
		Application app;
		app.run();

		glfwTerminate();
	}
}