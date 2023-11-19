#include "pch.h"
#include "application.h"

int main()
{
	Debug::LogSuccess("Launching PwAG Space Shooter Game...");

	if (glfwInit() == GLFW_TRUE)
	{
		Application app;
		app.run();

		glfwTerminate();
	}
}