#include <Renderer/Systems/BufferSystem.h>
#include <Renderer/Components/Buffer.h>

#include <Core/World.h>
#include <Gameplay/Components/Mesh.h>

#include <glad/glad.h>


namespace
{
	using namespace RocketEngine;

	auto createBuffer(MeshBuffer& buffer, const StaticMesh& mesh)
	{
		glGenVertexArrays(1, &buffer.vao);
		glGenBuffers(1, &buffer.vbo);
		glGenBuffers(1, &buffer.ebo);

		glBindVertexArray(buffer.vao);

		glBindBuffer(GL_ARRAY_BUFFER, buffer.vbo);
		glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Vertex), mesh.vertices.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer.ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(unsigned int), mesh.indices.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	}

	auto deleteBuffer(MeshBuffer& buffer)
	{
		glDeleteVertexArrays(1, &buffer.vao);
		glDeleteBuffers(1, &buffer.vbo);
	}
}

namespace RocketEngine
{
	BufferSystem::BufferSystem(World* world)
		: System(world)
	{
	}

	auto BufferSystem::begin() -> void
	{
		for (auto [entity, mesh] : world->getEntities<const StaticMesh>())
		{
			auto& buffer = world->addComponents<MeshBuffer>(entity);
			createBuffer(buffer, mesh);
			buffer.size = mesh.indices.size();
		}
	}

	auto BufferSystem::update(double dt) -> void
	{
	}

	auto BufferSystem::end() -> void
	{
		for (auto [entity, buffer] : world->getEntities<MeshBuffer>())
		{
			deleteBuffer(buffer);
		}
	}
}