project "GameWorld"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "PrecompiledHeader.h"
	pchsource "Source/GameWorld/Pch/PrecompiledHeader.cpp"
	
	files
	{
		"Source/**.h",
		"Source/**.cpp",
		"ThirdParty/glm/glm/**.hpp",
		"ThirdParty/glm/glm/**.inl",
	}
	
	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}
	
	includedirs
	{
		"Source",
		"ThirdParty/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.IMGUI}",
		"%{IncludeDir.GLM}",
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