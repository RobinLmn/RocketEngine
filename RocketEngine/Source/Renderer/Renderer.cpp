#include <Renderer/Renderer.h>

#include <Renderer/Systems/ShaderSystem.h>
#include <Renderer/Systems/BufferSystem.h>
#include <Renderer/Components/Buffer.h>

#include <Gameplay/Components/Material.h>
#include <Gameplay/Components/Light.h>
#include <Gameplay/Components/Transform.h>

#include <Core/World.h>

#include <glad/glad.h>
#include <vector>
#include <glm/gtc/type_ptr.hpp>

namespace
{
	using namespace RocketEngine;

	auto setClearColor(float r, float g, float b, float a) -> void
	{
		glEnable(GL_DEPTH_TEST);
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}

namespace RocketEngine
{
	Renderer::Renderer(World* world)
		: world{ world }
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

		glm::mat4 viewProj{};
		glm::vec3 viewPos{};
		for (auto [entity, cameraBuffer, transform] : world->getEntities<const CameraBuffer, const Transform>())
		{
			viewProj = cameraBuffer.viewProjection;
			viewPos = transform.position;
			break;
		}

		Light light{};
		for (auto [entity, lightComp] : world->getEntities<const Light>())
		{
			light = lightComp;
			break;
		}

		for (auto [entity, meshBuffer, objectBuffer, material] : world->getEntities<const MeshBuffer, const ObjectBuffer, const Material>())
		{
			glUniformMatrix4fv(glGetUniformLocation(meshBuffer.shader, "viewProj"), 1, GL_FALSE, glm::value_ptr(viewProj));
			glUniformMatrix4fv(glGetUniformLocation(meshBuffer.shader, "model"), 1, GL_FALSE, glm::value_ptr(objectBuffer.model));
			glUniform3fv(glGetUniformLocation(meshBuffer.shader, "viewPos"), 1, &viewPos[0]);

			// todo: replace by uniform object buffer
			glUniform3fv(glGetUniformLocation(meshBuffer.shader, "light.position"), 1, &light.position[0]);
			glUniform3fv(glGetUniformLocation(meshBuffer.shader, "light.ambient"), 1, &light.ambient[0]);
			glUniform3fv(glGetUniformLocation(meshBuffer.shader, "light.specular"), 1, &light.specular[0]);
			glUniform3fv(glGetUniformLocation(meshBuffer.shader, "light.diffuse"), 1, &light.diffuse[0]);

			// todo: replace by uniform object buffer
			glUniform3fv(glGetUniformLocation(meshBuffer.shader, "material.ambient"), 1, &material.ambient[0]);
			glUniform3fv(glGetUniformLocation(meshBuffer.shader, "material.specular"), 1, &material.specular[0]);
			glUniform3fv(glGetUniformLocation(meshBuffer.shader, "material.diffuse"), 1, &material.diffuse[0]);
			glUniform1f(glGetUniformLocation(meshBuffer.shader, "material.shininess"), material.shininess);

			glUseProgram(meshBuffer.shader);
			glBindVertexArray(meshBuffer.vao);
			glDrawElements(GL_TRIANGLES, (GLsizei)meshBuffer.size, GL_UNSIGNED_INT, 0);
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
