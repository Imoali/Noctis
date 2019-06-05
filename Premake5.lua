workspace "Noctis"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Noctis"
	location "Noctis"
	kind "SharedLib"
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
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.17763.0"

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
		symbols "On"

	filter "configurations:Release"
		defines "NT_RELEASE"
		symbols "On"

	filter "configurations:Dist"
		defines "NT_DIST"
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
		"Noctis/src"
	}

	links {
		"Noctis"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.17763.0"

	defines 
	{
		"NT_PLATFORM_WINDOWS",
		"_WINDLL"
	}

	filter "configurations:Debug"
		defines "NT_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "NT_RELEASE"
		symbols "On"

	filter "configurations:Dist"
		defines "NT_DIST"
		symbols "On"
