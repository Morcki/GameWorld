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
	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};
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

		/*
		 * Compute The Size of ShaderDataType
		 */
		static GW_UINT32 ShaderDataTypeSize(ShaderDataType type)
		{
			switch (type)
			{
			case ShaderDataType::Float:    return 4;
			case ShaderDataType::Float2:   return 4 * 2;
			case ShaderDataType::Float3:   return 4 * 3;
			case ShaderDataType::Float4:   return 4 * 4;
			case ShaderDataType::Mat3:     return 4 * 3 * 3;
			case ShaderDataType::Mat4:     return 4 * 4 * 4;
			case ShaderDataType::Int:      return 4;
			case ShaderDataType::Int2:     return 4 * 2;
			case ShaderDataType::Int3:     return 4 * 3;
			case ShaderDataType::Int4:     return 4 * 4;
			case ShaderDataType::Bool:     return 1;
			}

			GAMEWORLD_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
		
		/*
		 * Compute The Count number of ShaderDataType
		 */
		static GW_UINT32 ShaderDataTypeCount(ShaderDataType type)
		{
			switch (type)
			{
			case ShaderDataType::Float:   return 1;
			case ShaderDataType::Float2:  return 2;
			case ShaderDataType::Float3:  return 3;
			case ShaderDataType::Float4:  return 4;
			case ShaderDataType::Mat3:    return 3; // 3* float3
			case ShaderDataType::Mat4:    return 4; // 4* float4
			case ShaderDataType::Int:     return 1;
			case ShaderDataType::Int2:    return 2;
			case ShaderDataType::Int3:    return 3;
			case ShaderDataType::Int4:    return 4;
			case ShaderDataType::Bool:    return 1;
			}

			GAMEWORLD_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	}
}