#include "pch.h"
#include "window.h"

/* --->>> GLFW callback functions <<<--- */
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


/* --->>> Constructors / Destructor <<<--- */
Window::Window(uint32_t width, uint32_t height, WindowMode mode, std::string title)
	: _width(width), _height(height), _mode(mode), _title(std::move(title))
{
	_initialize();
}

Window::~Window()
{
	if (_glfwWindowPtr)
	{
		glfwDestroyWindow(_glfwWindowPtr);
		_glfwWindowPtr = nullptr;
	}
}


/* --->>> Event system <<<--- */
void Window::attachEventManager(EventManager& manager)
{
	_eventManager = &manager;
	glfwSetWindowCloseCallback(_glfwWindowPtr, window_close_callback);
	glfwSetFramebufferSizeCallback(_glfwWindowPtr, framebuffer_size_callback);
	glfwSetKeyCallback(_glfwWindowPtr, key_callback);
	glfwSetMouseButtonCallback(_glfwWindowPtr, mouse_button_callback);
	glfwSetCursorPosCallback(_glfwWindowPtr, cursor_position_callback);

	glfwSetWindowUserPointer(_glfwWindowPtr, reinterpret_cast<void*>(this));
}

#pragma region GLFW->Event manager callbacks
void Window::windowCloseCallback(bool shouldCloseWindow)
{
	_eventManager->windowCloseCallback(shouldCloseWindow);
}

void Window::windowResizeCallback(int width, int height)
{
	_eventManager->windowSizeCallback(width, height);
}

void Window::keyCallback(int key, int scancode, int action, int mods)
{
	_eventManager->keyCallback(key, scancode, action, mods);
}

void Window::mouseButtonCallback(int button, int action, int mods)
{
	_eventManager->mouseButtonCallback(button, action, mods);
}

void Window::cursorPositionCallback(double x, double y)
{
	_eventManager->cursorPositionCallback(x, y);
}
#pragma endregion


/* --->>> Initialization <<<--- */
void Window::_initialize()
{
	_createGLFWWindow();
	_initOpenGL();
}

void Window::_initOpenGL() const
{
	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		Debug::LogError("Failed to initialize OpenGL context");
		exit;
	}

	glViewport(0, 0, _width, _height);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Window::_createGLFWWindow()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	switch (_mode)
	{
	case WindowMode::eWindowed:
		_createWindowedWindow();
		break;
	case WindowMode::eFullscreen:
		_createFullscreenWindow();
		break;
	case WindowMode::eWindowFullscreen:
		_createWindowedFullscreenWindow();
		break;
	}

	glfwMakeContextCurrent(_glfwWindowPtr);
	_createWindowIcon();
}

void Window::_createWindowedWindow()
{
	_glfwWindowPtr = glfwCreateWindow(_width, _height, Config::g_defaultWindowTitle, nullptr, nullptr);
	_centerWindow();
}

void Window::_createFullscreenWindow()
{
	const auto monitor = glfwGetPrimaryMonitor();
	_glfwWindowPtr = glfwCreateWindow(_width, _height, Config::g_defaultWindowTitle, monitor, nullptr);
}

void Window::_createWindowedFullscreenWindow()
{
	const auto monitor = glfwGetPrimaryMonitor();
	const auto videoMode = glfwGetVideoMode(monitor);

	glfwWindowHint(GLFW_RED_BITS, videoMode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, videoMode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, videoMode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, videoMode->refreshRate);

	_width = videoMode->width;
	_height = videoMode->height;
}


/* --->>> Configuration <<<--- */
void Window::_centerWindow() const
{
	if (const auto monitor = glfwGetPrimaryMonitor())
	{
		if (const auto videoMode = glfwGetVideoMode(monitor))
		{
			int monitorX, monitorY;
			glfwGetMonitorPos(monitor, &monitorX, &monitorY);

			int windowWidth, windowHeight;
			glfwGetWindowSize(_glfwWindowPtr, &windowWidth, &windowHeight);

			glfwSetWindowPos(_glfwWindowPtr, monitorX + (videoMode->width - windowWidth) / 2, monitorY + (videoMode->height - windowHeight) / 2);
		}
	}
}

void Window::_createWindowIcon()
{
	// Load image
	int width, height;
	int channels;
	unsigned char* pixels = stbi_load("res/Textures/DevLogo.png", &width, &height, &channels, 4);

	// Change window icon
	GLFWimage images[1];
	images[0].width = width;
	images[0].height = height;
	images[0].pixels = pixels;

	glfwSetWindowIcon(_glfwWindowPtr, 1, images);
}

