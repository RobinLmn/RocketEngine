workspace "RocketEngine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "RocketEngine/ThirdParty/glfw"

project "RocketEngine"
	location "RocketEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "On"

	targetdir ("Build/" .. outputdir .. "/%{prj.name}")
	objdir ("Intermediate/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp",
		"%{prj.name}/ThirdParty/glad/src",
	}

	includedirs
	{
		"%{prj.name}/Source",
		"%{prj.name}/ThirdParty/spdlog",
		"%{prj.name}/ThirdParty/glm",
		"%{prj.name}/ThirdParty/glfw/include",
		"%{prj.name}/ThirdParty/entt/src",
		"%{prj.name}/ThirdParty/tinyobjloader",
		"%{prj.name}/ThirdParty/glad/include",
	}

	links
	{
		"glfw",
	}

	filter "system:windows"
		systemversion "10.0"

	filter "configurations:Debug"
		defines {"ROCKET_DEBUG"}
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		runtime "Release"
		optimize "on"

project "RocketGame"
	location "RocketGame"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "On"

	targetdir ("Build/" .. outputdir .. "/%{prj.name}")
	objdir ("Intermediate/" .. outputdir .. "/%{prj.name}")

	files
	{ 
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp",
		"RocketEngine/ThirdParty/glad/src/glad.c",
	}

	includedirs
	{
		"%{prj.name}/Source",
		"RocketEngine/Source",
		"RocketEngine/ThirdParty/entt/src",
		"RocketEngine/ThirdParty/spdlog",
		"RocketEngine/ThirdParty/glad/include",
		"RocketEngine/ThirdParty/glm",
	}

	links
	{
		"RocketEngine"
	}

	filter "system:windows"
		systemversion "10.0"

	filter "configurations:Debug"
		defines {"ROCKET_DEBUG"}
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		runtime "Release"
		optimize "on"

project "RocketEditor"
	location "RocketEditor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "On"

	targetdir ("Build/" .. outputdir .. "/%{prj.name}")
	objdir ("Intermediate/" .. outputdir .. "/%{prj.name}")

	files
	{ 
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp",
		"RocketEngine/ThirdParty/glad/src/glad.c",
	}

	includedirs
	{
		"%{prj.name}/Source",
		"RocketEngine/Source",
		"RocketEngine/ThirdParty/entt/src",
		"RocketEngine/ThirdParty/spdlog",
		"RocketEngine/ThirdParty/glad/include",
		"RocketEngine/ThirdParty/glm",
	}

	links
	{
		"RocketEngine"
	}

	filter "system:windows"
		systemversion "10.0"

	filter "configurations:Debug"
		defines {"ROCKET_DEBUG"}
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		runtime "Release"
		optimize "on"