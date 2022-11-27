#include <Systems/Editor.h>

#include <Core/Engine.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glfw/glfw3.h>


namespace RocketEditor
{
	Editor::Editor(RocketEngine::World* world)
		: System(world)
	{
	}

	auto Editor::begin() -> void
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		auto& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

		ImGui::StyleColorsDark();

		auto& engine = RocketEngine::Engine::get();
		ImGui_ImplGlfw_InitForOpenGL(engine.getNativeWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 450");

		engine.pushRenderCallback([&]() { render(); });
	}

	auto Editor::update(double dt) -> void
	{
		newFrame();

		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Hello, world!");                          
		ImGui::Text("This is some useful text.");             
		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);     

		if (ImGui::Button("Button")) counter++;

		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	auto Editor::newFrame() -> void
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	auto Editor::render() -> void
	{
		ImGuiIO& io = ImGui::GetIO();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* oldContext = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(oldContext);
		}
	}

	auto Editor::end() -> void
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
}