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

		auto isKeyPressed(int key) const -> bool;
		auto getAspectRatio() const -> float;
		[[nodiscard]] auto getNativeWindow() -> GLFWwindow*;

	private:
		GLFWwindow* window;
	};
}