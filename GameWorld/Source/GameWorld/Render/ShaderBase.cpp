#include <PrecompiledHeader.h>

#include "ShaderBase.h"

#include "glad/glad.h"

namespace GameWorld
{

	ShaderBase::ShaderBase()
	{
		ShaderProgramID = glCreateProgram();
	}

	ShaderBase::~ShaderBase()
	{
		glDeleteProgram(ShaderProgramID);
	}

	void ShaderBase::LinkShaderFile(const GW_CHAR* vertexPath, const GW_CHAR* fragmentPath, const GW_CHAR* geometryPath)
	{
		GW_BOOL bCompileOk = LoadShaderFile(vertexPath, ShaderConst::VERTEX) & LoadShaderFile(fragmentPath, ShaderConst::FRAGMENT);
		if (geometryPath != nullptr)
		{
			bCompileOk &= LoadShaderFile(geometryPath, ShaderConst::GEOMETRY);
		}

		if (!bCompileOk) return;
		
		glLinkProgram(ShaderProgramID);
		bCompileOk &= CheckShaderCompile(ShaderProgramID, ShaderConst::PROGRAM);

		if (!bCompileOk) return;

		glDeleteShader(ShaderVertexID);
		glDeleteShader(ShaderFragmentID);
		if (geometryPath != nullptr)
		{
			glDeleteShader(ShaderGeometryID);
		}
	}

	void ShaderBase::UseShader()
	{
		glUseProgram(ShaderProgramID);
	}

	void ShaderBase::DeleteShader()
	{
		glUseProgram(0);
	}

	GW_BOOL ShaderBase::LoadShaderFile(const GW_CHAR* shaderFilePath, ShaderType type)
	{
		std::string shaderCode;
		std::ifstream shaderFile;
		shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// open files
			shaderFile.open(shaderFilePath);
			std::stringstream shaderStream;
			// read file's buffer contents into streams
			shaderStream << shaderFile.rdbuf();
			
			// close file handlers
			shaderFile.close();
			// convert stream into string
			shaderCode = shaderStream.str();
		}
		catch (std::ifstream::failure& e)
		{
			GAMEWORLD_CORE_ERROR
			(
				"shader::cannot load shader file!\n\tShader Type : {0}\n\tShader File : {1}",
				ShaderTool::ShaderTypeToString(type), shaderFilePath
			);
			GAMEWORLD_CORE_ASSERT(false, "Please input correct Shader File Path!");
		}
		const char* code = shaderCode.c_str();
		GW_BOOL bCompileSuccess = false;
		switch(type)
		{
			case ShaderConst::VERTEX:
			{
				ShaderVertexID = glCreateShader(GL_VERTEX_SHADER);
				glShaderSource(ShaderVertexID, 1, &code, NULL);
				glCompileShader(ShaderVertexID);
				bCompileSuccess = CheckShaderCompile(ShaderVertexID, type);
				glAttachShader(ShaderProgramID, ShaderVertexID);
				break;
			}
			case ShaderConst::FRAGMENT:
			{
				ShaderFragmentID = glCreateShader(GL_FRAGMENT_SHADER);
				glShaderSource(ShaderFragmentID, 1, &code, NULL);
				glCompileShader(ShaderFragmentID);
				bCompileSuccess = CheckShaderCompile(ShaderFragmentID, type);
				glAttachShader(ShaderProgramID, ShaderFragmentID);
				break;
			}
			case ShaderConst::GEOMETRY:
			{
				ShaderGeometryID = glCreateShader(GL_GEOMETRY_SHADER);
				glShaderSource(ShaderGeometryID, 1, &code, NULL);
				glCompileShader(ShaderGeometryID);
				bCompileSuccess = CheckShaderCompile(ShaderGeometryID, type);
				glAttachShader(ShaderProgramID, ShaderGeometryID);
				break;
			}
			default:
			{
				GAMEWORLD_CORE_ERROR("shader::wrong shader type!");
				break;
			}
		}
		return bCompileSuccess;
	}

	GW_BOOL ShaderBase::CheckShaderCompile(GW_UINT32 shader, ShaderType type)
	{
		int success;
		char infoLog[1024];
		if (type != ShaderConst::PROGRAM)
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				GAMEWORLD_CORE_ERROR
					("shader::compile shader error!\nShader Type : {0}\n{1}\n -- --------------------------------------------------- -- ",
						ShaderTool::ShaderTypeToString(type), infoLog);
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				GAMEWORLD_CORE_ERROR
					("shader::link shader error!\nShader Type : {0}\n{1}\n -- --------------------------------------------------- -- ",
						ShaderTool::ShaderTypeToString(type), infoLog);
			}
		}
		return (success ^ 0);
	}
}

