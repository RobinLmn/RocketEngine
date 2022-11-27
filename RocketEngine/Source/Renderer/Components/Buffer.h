#pragma once

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
}