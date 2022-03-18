#pragma once
#include <string>
#include "GameWorld/Log/Log.h"
namespace GameWorld
{
	using ShaderType = uint16_t;
	namespace ShaderConst
	{
		enum ShaderType
		{
			VERTEX,
			FRAGMENT,
			GEOMETRY,

			PROGRAM
		};
	}
	namespace ShaderTool
	{
		static const std::string ShaderTypeToString(ShaderType type)
		{
			std::string shaderTypeString;
			switch(type)
			{
			case ShaderConst::VERTEX:
				shaderTypeString = "Vertex";
				break;
			case ShaderConst::FRAGMENT:
				shaderTypeString = "Fragment";
				break;
			case ShaderConst::GEOMETRY:
				shaderTypeString = "Geometry";
				break;
			case ShaderConst::PROGRAM:
				shaderTypeString = "Program";
				break;
			default:
				GAMEWORLD_CORE_ERROR("shader::wrong shader type!");
				shaderTypeString = "";
				break;
			}
			return shaderTypeString;
		}
	}
}