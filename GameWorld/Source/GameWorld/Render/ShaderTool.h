#pragma once
#include <string>
#include "GameWorld/Log/Log.h"

#include "glm/glm.hpp"

namespace GameWorld
{
	enum class ShaderType
	{
		kVertex,
		kFragment,
		kGeometry,

		kProgram
	};

	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};
	class ShaderTool
	{
	public:

		static const std::string ShaderTypeToString(ShaderType type);
		
		/*
		 * Compute The Size of ShaderDataType
		 */
		static GW_UINT32 ShaderDataTypeSize(ShaderDataType type);
		
		/*
		 * Compute The Count number of ShaderDataType
		 */
		static GW_UINT32 ShaderDataTypeCount(ShaderDataType type);
		
		static void SetBoolUniform(GW_UINT32 program_id, const std::string &name, GW_BOOL value);
		
		static void SetIntUniform(GW_UINT32 program_id, const std::string &name, GW_INT32 value);
		
		static void SetFloatUniform(GW_UINT32 program_id, const std::string &name, GW_FLOAT32 value);
		
		static void SetVec3Uniform(GW_UINT32 program_id, const std::string &name, GW_FLOAT32 v1, GW_FLOAT32 v2, GW_FLOAT32 v3);

		static void SetVec3Uniform(GW_UINT32 program_id, const std::string &name, const glm::vec3& val);
		
		static void SetVec4Uniform(GW_UINT32 program_id, const std::string &name, GW_FLOAT32 v1, GW_FLOAT32 v2, GW_FLOAT32 v3, GW_FLOAT32 v4);

		static void SetVec4Uniform(GW_UINT32 program_id, const std::string &name, const glm::vec4& val);
		
		static void SetMat4Uniform(GW_UINT32 program_id, const std::string &name, GW_FLOAT32 *mat4);

		static void SetMat4Uniform(GW_UINT32 program_id, const std::string &name, glm::mat4& mat4);

		static void SetMat4Uniform(GW_UINT32 program_id, const std::string &name, const glm::mat4& mat4);
	};
}