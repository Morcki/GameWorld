project "SandBox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"
	
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"Source/**.h",
		"Source/**.cpp"
	}
	
	includedirs
	{
		"%{wks.location}/GameWorld/ThirdParty/spdlog/include",
		"%{wks.location}/GameWorld/Source",
		"%{wks.location}/GameWorld/ThirdParty",
		"%{IncludeDir.GLM}",
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
		buildoptions "/MTd"
		symbols "On"
		
	filter "configurations:Release"
		defines "GAMEWORLD_RELEASE"
		runtime "Release"
		buildoptions "/MT"
		symbols "On"
	
	filter "configurations:Dist"
		defines "GAMEWORLD_DIST"
		runtime "Release"
		buildoptions "/MT"
		symbols "On"