#include <Gameplay/Systems/MeshLoadingSystem.h>

#define TINYOBJLOADER_IMPLEMENTATION

#include <tinyobjloader/tiny_obj_loader.h>
#include <iostream>

#include <Core/Engine.h>
#include <Gameplay/Components/Mesh.h>

namespace RocketEngine
{
    MeshLoadingSystem::MeshLoadingSystem(World* world)
        : System(world)
    {
    }

    auto MeshLoadingSystem::begin() -> void
    {
        for (auto [entity, pathComponent] : world->getEntities<const Model>())
        {
            auto& mesh = world->addComponents<StaticMesh>(entity);
            loadMesh(&mesh, pathComponent.path.c_str());
        }
    }

    auto MeshLoadingSystem::loadMesh(StaticMesh* mesh, const char * path) -> void
    {
        tinyobj::ObjReaderConfig readerConfig;
        readerConfig.mtl_search_path = "../../RocketEngine/Content/Models";
        tinyobj::ObjReader reader;

        if (!reader.ParseFromFile(path, readerConfig))
        {
            if (!reader.Error().empty())
            {
                std::cerr << "TinyObjReader: " << reader.Error();
            }
            exit(1);
        }

        if (!reader.Warning().empty())
        {
            std::cout << "TinyObjReader: " << reader.Warning();
        }

        auto& attrib = reader.GetAttrib();
        auto& shapes = reader.GetShapes();
        auto& materials = reader.GetMaterials();

        size_t i = 0;
        for (size_t s = 0; s < shapes.size(); s++)
        {
            size_t index_offset = 0;
            for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
            {
                size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);
                size_t materialID = shapes[s].mesh.material_ids[f];

                // Loop over vertices in the face.
                for (size_t v = 0; v < fv; v++)
                {
                    tinyobj::index_t idx = shapes[s].mesh.indices[index_offset];
                    
                    // position
                    tinyobj::real_t vx = attrib.vertices[3 * idx.vertex_index + 0];
                    tinyobj::real_t vy = attrib.vertices[3 * idx.vertex_index + 1];
                    tinyobj::real_t vz = attrib.vertices[3 * idx.vertex_index + 2];

                    tinyobj::real_t nx = 0;
                    tinyobj::real_t ny = 0;
                    tinyobj::real_t nz = 0;

                    if (idx.normal_index >= 0)
                    {
                        nx = attrib.normals[3 * idx.normal_index +0];
                        ny = attrib.normals[3 * idx.normal_index +1];
                        nz = attrib.normals[3 * idx.normal_index +2];
                    }
                    index_offset++;
                    i++;
                }
            }
        }
    }
}
