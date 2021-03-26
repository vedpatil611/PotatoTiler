workspace "PotatoTiler"
	architecture "x64"
	startproject "PotatoTiler"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Dependencies/GLFW"

IncludeDirs = {}
IncludeDirs["GLFW"] = "Dependencies/GLFW/include"

project "PotatoTiler"
	location "PotatoTiler"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	systemversion "latest"

	inlining "Auto"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("intermediate/" .. outputdir .. "/%{prj.name}")

	includedirs {
		"%{prj.name}/src/",
		"%{IncludeDirs.GLFW}"
	}

	links {
		"GLFW",
		"opengl32"
	}

	files { 
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.cpp"
	}

	filter "system:windows"
		defines {
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "RELEASE" }
		optimize "On"
		buildoptions "/MD"