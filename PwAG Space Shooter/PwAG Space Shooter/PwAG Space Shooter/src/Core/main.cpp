#include "pch.h"
#include "application.h"

int main()
{
	Debug::LogSuccess("Launching Hunters of empire...");

	if (glfwInit() == GLFW_TRUE)
	{
		Application app;
		app.run();

		glfwTerminate();
	}
}