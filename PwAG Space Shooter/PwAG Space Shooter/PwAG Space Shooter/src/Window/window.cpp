#include "pch.h"
#include "window.h"

#pragma region GLFW callback functions
void framebuffer_size_callback(GLFWwindow* window, const int width, const int height)
{
	glViewport(0, 0, width, height);
	auto* userWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
	if (userWindow)
	{
		userWindow->windowResizeCallback(width, height);
	}
}

void window_close_callback(GLFWwindow* window)
{
	auto* userWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
	if (userWindow)
	{
		userWindow->windowCloseCallback(glfwWindowShouldClose(window));
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	auto* userWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
	if (userWindow)
	{
		userWindow->keyCallback(key, scancode, action, mods);
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	auto* userWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
	if (userWindow)
	{
		userWindow->mouseButtonCallback(button, action, mods);
	}
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	auto* userWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
	if (userWindow)
	{
		userWindow->cursorPositionCallback(xpos, ypos);
	}
}
#pragma endregion

Window::Window(uint32_t width, uint32_t height, WindowMode mode, std::string title)
	: width(width), height(height), mode(mode), title(std::move(title))
{
	initialize();
}

Window::~Window()
{
	if(glfwWindowPtr)
	{
		glfwDestroyWindow(glfwWindowPtr);
		glfwWindowPtr = nullptr;
	}
}

void Window::attachEventManager(EventManager& manager)
{
	this->eventManager = &manager;

	glfwSetWindowCloseCallback(glfwWindowPtr, window_close_callback);
	glfwSetFramebufferSizeCallback(glfwWindowPtr, framebuffer_size_callback);
	glfwSetKeyCallback(glfwWindowPtr, key_callback);
	glfwSetMouseButtonCallback(glfwWindowPtr, mouse_button_callback);
	glfwSetCursorPosCallback(glfwWindowPtr, cursor_position_callback);

	glfwSetWindowUserPointer(glfwWindowPtr, reinterpret_cast<void*>(this));
}

#pragma region GLFW->Event manager callbacks
void Window::windowCloseCallback(bool shouldCloseWindow)
{
	eventManager->windowCloseCallback(shouldCloseWindow);
}

void Window::windowResizeCallback(int width, int height)
{
	eventManager->windowSizeCallback(width, height);
}

void Window::keyCallback(int key, int scancode, int action, int mods)
{
	eventManager->keyCallback(key, scancode, action, mods);
}

void Window::mouseButtonCallback(int button, int action, int mods)
{
	eventManager->mouseButtonCallback(button, action, mods);
}

void Window::cursorPositionCallback(double x, double y)
{
	eventManager->cursorPositionCallback(x, y);
}
#pragma endregion

void Window::initialize()
{
	createGLFWWindow();
	initOpenGL();
}

void Window::createGLFWWindow()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	switch (mode)
	{
	case WindowMode::eWindowed:
		createWindowedWindow();
		break;
	case WindowMode::eFullscreen:
		createFullscreenWindow();
		break;
	case WindowMode::eWindowFullscreen:
		createWindowedFullscreenWindow();
		break;
	}
	glfwMakeContextCurrent(glfwWindowPtr);
	
	//glfwSetWindowIcon();
}

void Window::createWindowedWindow()
{
	glfwWindowPtr = glfwCreateWindow(width, height, Config::g_defaultWindowTitle, nullptr, nullptr);
	centerWindow();
}

void Window::createFullscreenWindow()
{
	const auto monitor = glfwGetPrimaryMonitor();
	glfwWindowPtr = glfwCreateWindow(width, height, Config::g_defaultWindowTitle, monitor, nullptr);
}

void Window::createWindowedFullscreenWindow()
{
	const auto monitor = glfwGetPrimaryMonitor();
	const auto videoMode = glfwGetVideoMode(monitor);

	glfwWindowHint(GLFW_RED_BITS, videoMode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, videoMode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, videoMode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, videoMode->refreshRate);

	width = videoMode->width;
	height = videoMode->height;
}

void Window::centerWindow() const
{
	if (const auto monitor = glfwGetPrimaryMonitor())
	{
		if (const auto videoMode = glfwGetVideoMode(monitor)) 
		{
			int monitorX, monitorY;
			glfwGetMonitorPos(monitor, &monitorX, &monitorY);

			int windowWidth, windowHeight;
			glfwGetWindowSize(glfwWindowPtr, &windowWidth, &windowHeight);

			glfwSetWindowPos(glfwWindowPtr, monitorX + (videoMode->width - windowWidth) / 2, monitorY + (videoMode->height - windowHeight) / 2);
		}
	}

}

void Window::initOpenGL() const
{
	if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		//TODO init exception
	}

	glViewport(0, 0, width, height);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

