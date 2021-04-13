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
include "Dependencies/GLAD"
include "Dependencies/ImGui"

IncludeDirs = {}
IncludeDirs["GLFW"] = "Dependencies/GLFW/include"
IncludeDirs["GLAD"] = "Dependencies/GLAD/include"
IncludeDirs["GLM"] = "Dependencies/glm"
IncludeDirs["SceneTree"] = "SceneTree/src"
IncludeDirs["ImGui"] = "Dependencies/Imgui/src"
IncludeDirs["ImGuiFileBrowser"] = "Dependencies/imgui-filebrowser"

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
		"%{IncludeDirs.GLFW}",
		"%{IncludeDirs.GLAD}",
		"%{IncludeDirs.GLM}",
		"%{IncludeDirs.SceneTree}",
		"%{IncludeDirs.ImGui}",
		"%{IncludeDirs.ImGuiFileBrowser}"
	}

	links {
		"GLFW",
		"GLAD",
		"SceneTree",
		"ImGui"
	}

	files { 
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/Renderer/**.h",
		"%{prj.name}/src/Renderer/**.cpp",
		"%{prj.name}/src/SceneTree/**.h",
		"%{prj.name}/src/SceneTree/**.cpp",
		"%{prj.name}/src/UI/**.h",
		"%{prj.name}/src/UI/**.cpp",
		"%{prj.name}/src/utils/**.h",
		"%{prj.name}/src/utils/**.cpp",
		"%{prj.name}/shaders/**.glsl"
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

project "SceneTree"
	location "SceneTree"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	systemversion "latest"

	inlining "Auto"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("intermediate/" .. outputdir .. "/%{prj.name}")

	includedirs {
		"%{prj.name}/src/",
		"%{IncludeDirs.GLM}"
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
