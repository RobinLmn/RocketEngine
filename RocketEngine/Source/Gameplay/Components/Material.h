#pragma once

#include <glm/glm.hpp>

namespace RocketEngine
{
	struct Shader
	{
		const char* vertexShader;
		const char* fragmentShader;
	};

	struct Material
	{
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		float shininess;
	};
}