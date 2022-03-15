include "Dependencies.lua"

workspace "GameWorld"
	architecture "x64"
	startproject "SandBox"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "GameWorld/ThirdParty/glfw"
	include "GameWorld/ThirdParty/glad"
	include "GameWorld/ThirdParty/imgui"
group ""

include "GameWorld"

project "SandBox"
	location "SandBox"
	kind "ConsoleApp"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp"
	}
	
	includedirs
	{
		"GameWorld/ThirdParty/spdlog/include",
		"GameWorld/Source"
	}
	
	links
	{
		"GameWorld"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"GAMEWORLD_PLATFORM_WINDOWS",
			"GAMEWORLD_ENABLE_ASSERT",
		}
		
	filter "configurations:Debug"
		defines "GAMEWORLD_DEBUG"
		buildoptions "/MDd"
		symbols "On"
		
	filter "configurations:Release"
		defines "GAMEWORLD_RELEASE"
		buildoptions "/MD"
		symbols "On"
	
	filter "configurations:Dist"
		defines "GAMEWORLD_DIST"
		buildoptions "/MD"
		symbols "On"