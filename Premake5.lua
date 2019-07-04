workspace "Noctis"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
	startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"]	= "Noctis/vendor/GLFW/include"
IncludeDir["Glad"]	= "Noctis/vendor/Glad/include"
IncludeDir["imgui"]	= "Noctis/vendor/imgui"
IncludeDir["glm"]	= "Noctis/vendor/glm"

include "Noctis/vendor/GLFW/"
include "Noctis/vendor/Glad/"
include "Noctis/vendor/imgui/"


project "Noctis"
	location "Noctis"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "ntpch.h"
	pchsource "Noctis/src/ntpch.cpp"

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.imgui}"
	}

	links {
		"GLFW",
		"Glad",
		"imgui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "off"
		systemversion "latest"

	defines 
	{
		"NT_PLATFORM_WINDOWS",
		"NT_BUILD_DLL",
		"_WINDLL"
	}

	postbuildcommands
	{
		{"{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/sandbox"}
	}

	filter "configurations:Debug"
		defines "NT_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "NT_RELEASE"
		runtime "Release"
		symbols "On"

	filter "configurations:Dist"
		defines "NT_DIST"
		runtime "Release"
		symbols "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Noctis/vendor/spdlog/include",
		"%{IncludeDir.glm}",
		"Noctis/src"
	}

	links {
		"Noctis"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "off"
		systemversion "latest"

	defines 
	{
		"NT_PLATFORM_WINDOWS",
		"_WINDLL"
	}

	filter "configurations:Debug"
		defines "NT_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "NT_RELEASE"
		runtime "Release"
		symbols "On"

	filter "configurations:Dist"
		defines "NT_DIST"
		runtime "Release"
		symbols "On"
