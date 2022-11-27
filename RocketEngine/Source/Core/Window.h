#pragma once

struct GLFWwindow;
namespace RocketEngine
{
	class Window final
	{
	public:
		Window(int width, int height, const char* title);
		~Window();

		auto isOpen() const -> bool;
		auto processInput() -> void;

	private:
		GLFWwindow* window;
	};
}