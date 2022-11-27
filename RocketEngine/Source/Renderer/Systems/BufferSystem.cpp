#include <Renderer/Systems/BufferSystem.h>
#include <Renderer/Components/Buffer.h>

#include <Core/World.h>
#include <Gameplay/Components/Mesh.h>
#include <Gameplay/Components/Transform.h>
#include <Gameplay/Components/Camera.h>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
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
		
		for (auto [entity, transform] : world->getEntities<const Transform>())
		{
			world->addComponents<ObjectBuffer>(entity);
		}

		for (auto [entity, camera] : world->getEntities<const Camera>())
		{
			world->addComponents<CameraBuffer>(entity);
		}
	}

	auto BufferSystem::update(double dt) -> void
	{
		for (auto [entity, transform, buffer] : world->getEntities<const Transform, ObjectBuffer>())
		{
			buffer.model = glm::mat4(1.0f);
			buffer.model = glm::translate(buffer.model, transform.position);
			buffer.model = glm::rotate(buffer.model, glm::radians(transform.rotation.x), glm::vec3(1.f, 0.f, 0.f));
			buffer.model = glm::rotate(buffer.model, glm::radians(transform.rotation.y), glm::vec3(0.f, 1.f, 0.f));
			buffer.model = glm::rotate(buffer.model, glm::radians(transform.rotation.z), glm::vec3(0.f, 0.f, 1.f));
			buffer.model = glm::scale(buffer.model, transform.scale);
		}

		for (auto [entity, camera, objectBuffer, buffer] : world->getEntities<const Camera, const ObjectBuffer, CameraBuffer>())
		{
			const auto projection = glm::perspective(glm::radians(camera.fov), camera.aspect, camera.near, camera.far);
			const auto view = objectBuffer.model;
			buffer.viewProjection = projection * view;
		}
	}

	auto BufferSystem::end() -> void
	{
		for (auto [entity, buffer] : world->getEntities<MeshBuffer>())
		{
			deleteBuffer(buffer);
		}
	}
}