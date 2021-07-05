workspace "Graphite"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Graphite/vendor/GLFW/include"
IncludeDir["Glad"] = "Graphite/vendor/Glad/include"
IncludeDir["ImGui"] = "Graphite/vendor/imgui"
IncludeDir["glm"] = "Graphite/vendor/glm"

include "Graphite/vendor/GLFW"
include "Graphite/vendor/Glad"
include "Graphite/vendor/imgui"

project "Graphite"
	location "Graphite"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "hzpch.h"
	pchsource "Graphite/src/hzpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"GP_PLATFORM_WINDOWS",
			"GP_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "GP_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "GP_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "GP_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Graphite/vendor/spdlog/include",
		"Graphite/src",
		"Graphite/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Graphite"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"GP_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "GP_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "GP_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "GP_DIST"
		runtime "Release"
		optimize "on"