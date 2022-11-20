#pragma once

namespace RocketEngine
{
    struct Camera
    {
        bool isMainCamera;
        
        float far;
        float near;
        float fov;
        float aspect;
        
        float speed;
        float sensitivity;
    };
}
