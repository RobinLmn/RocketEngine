#include <Core/Window.h>

#include <glad/glad.h>
#include <glfw/glfw3.h>

namespace
{
	auto windowResizeCallback(GLFWwindow* window, int width, int height) -> void
	{
		glViewport(0, 0, width, height);
	}
}

namespace RocketEngine
{
	Window::Window(int width, int height, const char* title)
	{
		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(width, height, title, nullptr, nullptr);

		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, windowResizeCallback);
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	}

	auto Window::isOpen() const -> bool
	{
		return !glfwWindowShouldClose(window);
	}

	auto Window::processInput() -> void
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	auto Window::isKeyPressed(int key) const -> bool
	{
		return glfwGetKey(window, key) == GLFW_PRESS;
	}

	auto Window::getAspectRatio() const -> float
	{
		int width, height;
		glfwGetWindowSize(window, &width, &height);
		return (float)width / (float)height;
	}

	auto Window::getNativeWindow() -> GLFWwindow*
	{
		return window;
	}

	Window::~Window()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}
}