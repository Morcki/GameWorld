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
include "SandBox"