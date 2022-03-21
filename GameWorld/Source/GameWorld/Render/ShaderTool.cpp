#include <PrecompiledHeader.h>
#include "ShaderTool.h"

#include "glad/glad.h"

namespace GameWorld
{

	const std::string ShaderTool::ShaderTypeToString(ShaderType type)
	{
		std::string shader_type_string;
		switch (type)
		{
		case ShaderConst::kVertex:
			shader_type_string = "Vertex";
			break;
		case ShaderConst::kFragment:
			shader_type_string = "Fragment";
			break;
		case ShaderConst::kGeometry:
			shader_type_string = "Geometry";
			break;
		case ShaderConst::kProgram:
			shader_type_string = "Program";
			break;
		default:
			GAMEWORLD_CORE_ERROR("shader::wrong shader type!");
			shader_type_string = "";
			break;
		}
		return shader_type_string;
	}

	GW_UINT32 ShaderTool::ShaderDataTypeSize(ShaderDataType type)
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

	GW_UINT32 ShaderTool::ShaderDataTypeCount(ShaderDataType type)
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

	void ShaderTool::SetBoolUniform(GW_UINT32 program_id, const std::string &name, GW_BOOL value)
	{
		glUniform1i(glGetUniformLocation(program_id, name.c_str()), (int)value);
	}

	void ShaderTool::SetIntUniform(GW_UINT32 program_id, const std::string &name, GW_INT32 value)
	{
		glUniform1i(glGetUniformLocation(program_id, name.c_str()), value);
	}

	void ShaderTool::SetFloatUniform(GW_UINT32 program_id, const std::string &name, GW_FLOAT32 value)
	{
		glUniform1f(glGetUniformLocation(program_id, name.c_str()), value);
	}

	void ShaderTool::SetVec3Uniform(GW_UINT32 program_id, const std::string &name, GW_FLOAT32 v1, GW_FLOAT32 v2, GW_FLOAT32 v3)
	{
		glUniform3f(glGetUniformLocation(program_id, name.c_str()), v1, v2, v3);
	}

	void ShaderTool::SetVec4Uniform(GW_UINT32 program_id, const std::string &name, GW_FLOAT32 v1, GW_FLOAT32 v2, GW_FLOAT32 v3, GW_FLOAT32 v4)
	{
		glUniform4f(glGetUniformLocation(program_id, name.c_str()), v1, v2, v3, v4);
	}

	void ShaderTool::SetMat4Uniform(GW_UINT32 program_id, const std::string &name, GW_FLOAT32 *mat4)
	{
		glUniformMatrix4fv(glGetUniformLocation(program_id, name.c_str()), 1, GL_FALSE, mat4);
	}

	void ShaderTool::SetMat4Uniform(GW_UINT32 program_id, const std::string &name, glm::mat4& mat4)
	{
		glUniformMatrix4fv(glGetUniformLocation(program_id, name.c_str()), 1, GL_FALSE, &mat4[0][0]);
	}

	void ShaderTool::SetMat4Uniform(GW_UINT32 program_id, const std::string &name, const glm::mat4& mat4)
	{
		glUniformMatrix4fv(glGetUniformLocation(program_id, name.c_str()), 1, GL_FALSE, &mat4[0][0]);
	}

}
