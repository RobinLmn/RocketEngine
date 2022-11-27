#include <Renderer/Renderer.h>

#include <Renderer/Systems/ShaderSystem.h>
#include <Renderer/Systems/BufferSystem.h>
#include <Renderer/Components/Buffer.h>

#include <Core/World.h>

#include <glad/glad.h>
#include <vector>

namespace
{
	using namespace RocketEngine;

	auto setClearColor(float r, float g, float b, float a) -> void
	{
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	auto drawBuffer(const MeshBuffer& buffer) -> void
	{
		glUseProgram(buffer.shader);
		glBindVertexArray(buffer.vao);
		glDrawElements(GL_TRIANGLES, (GLsizei)buffer.size, GL_UNSIGNED_INT, 0);
	}
}

namespace RocketEngine
{
	Renderer::Renderer(World* world)
		: world{world}
	{
		addSystem<BufferSystem>();
		addSystem<ShaderSystem>();
	}

	auto Renderer::begin() -> void
	{
		for (auto system : systems)
		{
			system->begin();
		}
	}

	auto Renderer::draw(double dt) -> void
	{
		setClearColor(0.12f, 0.55f, 0.77f, 1.0f);

		for (auto system : systems)
		{
			system->update(dt);
		}

		for (auto [entity, buffer] : world->getEntities<const MeshBuffer>())
		{
			drawBuffer(buffer);
		}
	}

	template<typename T_System>
	auto Renderer::addSystem() -> void
	{
		systems.push_back(new T_System{ world });
	}

	auto Renderer::end() -> void
	{
		for (auto system : systems)
		{
			system->end();
		}
	}

	Renderer::~Renderer()
	{
		for (auto system : systems)
		{
			delete system;
		}
	}
}