#include <Renderer/Systems/ShaderSystem.h>

#include <fstream>
#include <sstream>

#include <Core/Log.h>
#include <Core/World.h>
#include <Gameplay/Components/Material.h>
#include <Renderer/Components/Buffer.h>

#include <glad/glad.h>

namespace
{
    auto checkCompileErrors(unsigned int shader, std::string type) -> void
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                ROCKET_ERROR("ERROR::SHADER_COMPILATION_ERROR of type: {0}\n{1}", type, infoLog);
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                ROCKET_ERROR("ERROR::PROGRAM_LINKING_ERROR of type: {0}\n{1}", type, infoLog);
            }
        }
    }

    auto createShader(const char* vertexPath, const char* fragmentPath) -> unsigned int
    {
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;

        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;

            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();

            vShaderFile.close();
            fShaderFile.close();

            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure& e)
        {
            ROCKET_ERROR("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ {0}", e.what());;
        }

        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        unsigned int vertex, fragment;

        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");

        unsigned int id = glCreateProgram();
        glAttachShader(id, vertex);
        glAttachShader(id, fragment);
        glLinkProgram(id);
        checkCompileErrors(id, "PROGRAM");

        glDeleteShader(vertex);
        glDeleteShader(fragment);

        return id;
    }
}

namespace RocketEngine
{
    ShaderSystem::ShaderSystem(World* world)
        : System(world)
    {
    }

    auto ShaderSystem::begin() -> void
    {   
        for (auto [entity, material, buffer] : world->getEntities<const Material, MeshBuffer>())
        {
            buffer.shader = createShader(material.vertexShader, material.fragmentShader);
        }
    }
}