#pragma once

#include <glm/glm.hpp>

namespace RocketEngine
{
	struct MeshBuffer
	{
		unsigned int vbo;
		unsigned int vao;
		unsigned int ebo;
		unsigned int shader;

		size_t size;
	};

	struct ObjectBuffer
	{
		glm::mat4 model; 
	};

	struct CameraBuffer
	{
		glm::mat4 viewProjection;
	};
}