workspace "GameWorld"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "GameWorld/ThirdParty/glfw/include"
IncludeDir["GLAD"] = "GameWorld/ThirdParty/glad/include"
IncludeDir["IMGUI"] = "GameWorld/ThirdParty/imgui"

include "GameWorld/ThirdParty/glfw"
include "GameWorld/ThirdParty/glad"
include "GameWorld/ThirdParty/imgui"

project "GameWorld"
	location "GameWorld"
	kind "SharedLib"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "PrecompiledHeader.h"
	pchsource "GameWorld/Source/GameWorld/Pch/PrecompiledHeader.cpp"
	
	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp"
	}
	
	includedirs
	{
		"GameWorld/Source/GameWorld",
		"GameWorld/ThirdParty/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.IMGUI}",
	}
	
	links
	{
		"GLFW",
		"GLAD",
		"ImGui",
		"opengl32.lib"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"GAMEWORLD_PLATFORM_WINDOWS",
			"GAMEWORLD_BUILD_DLL",
			"GAMEWORLD_ENABLE_ASSERT",
			"GLFW_INCLUDE_NONE",
		}
		
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/SandBox")
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