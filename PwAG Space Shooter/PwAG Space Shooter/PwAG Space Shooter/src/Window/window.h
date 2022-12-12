#pragma once
#include "windowMode.h"

class Window
{
public:
	explicit Window(uint32_t width = Config::g_defaultWidth, uint32_t height = Config::g_defaultHeight, WindowMode mode = Config::g_defaultWindowMode, std::string title = Config::g_defaultWindowTitle);
	~Window();

#pragma region Inline functions
	// clear window to RGB color (0 - 255 values)
	void clearToColor(uint8_t red, uint8_t green, uint8_t blue) const
	{
		constexpr float inverseOfMaxValue = 1.0f / 255.0f;
		glClearColor(red * inverseOfMaxValue, green * inverseOfMaxValue, blue * inverseOfMaxValue, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	// clear window to RGB values (0.0f - 1.0f values)
	void clearToColorf(float red, float green, float blue) const
	{
		glClearColor(red, green, blue, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	// show rendered things on window
	void swapBuffers() const
	{
		glfwSwapBuffers(glfwWindowPtr);
	}

	GLFWwindow*& getGLFWWindow()
	{
		return glfwWindowPtr;
	}

	uint32_t getWidth() const
	{
		return width;
	}
	uint32_t getHeight() const
	{
		return height;
	}
	WindowMode getWindowMode() const
	{
		return mode;
	}
	const std::string& getTitle() const
	{
		return title;
	}
#pragma endregion

#pragma region Event system
	void attachEventManager(EventManager& manager);

	void windowCloseCallback(bool shouldCloseWindow);
	void windowResizeCallback(int width, int height);
	void keyCallback(int key, int scancode, int action, int mods);
	void mouseButtonCallback(int button, int action, int mods);
	void cursorPositionCallback(double x, double y);
#pragma endregion

private:
	void initialize();

	void initOpenGL() const;
	void createGLFWWindow();

	void createWindowedWindow();
	void createFullscreenWindow();
	void createWindowedFullscreenWindow();

	void centerWindow() const;

	GLFWwindow* glfwWindowPtr{};

	uint32_t width;
	uint32_t height;

	WindowMode mode;

	std::string title;

	EventManager* eventManager{};
};