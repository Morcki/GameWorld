#include <PrecompiledHeader.h>
#include "OpenGLShader.h"

#include "glad/glad.h"

namespace GameWorld
{
	constexpr GW_INT8* ShaderPragmaInclude = "#pragma include";

	OpenGLShader::OpenGLShader()
	{
		ShaderProgramID = glCreateProgram();
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(ShaderProgramID);
	}

	void OpenGLShader::LinkShaderFile(const GW_CHAR* vertexPath, const GW_CHAR* fragmentPath, const GW_CHAR* geometryPath)
	{
		GW_BOOL bCompileOk = LoadShaderFile(vertexPath, ShaderType::kVertex) & LoadShaderFile(fragmentPath, ShaderType::kFragment);
		if (geometryPath)
		{
			bCompileOk &= LoadShaderFile(geometryPath, ShaderType::kGeometry);
		}

		if (!bCompileOk) return;

		glLinkProgram(ShaderProgramID);
		bCompileOk &= CheckCompileResult(ShaderProgramID, ShaderType::kProgram);

		if (!bCompileOk) return;

		glDeleteShader(ShaderVertexID);
		glDeleteShader(ShaderFragmentID);
		if (geometryPath)
		{
			glDeleteShader(ShaderGeometryID);
		}
	}

	void OpenGLShader::LinkSourceCode(const std::string& vertexCode, const std::string& fragmentCode, const std::string& geometryCode)
	{
		GW_BOOL bCompileOk = CompileShader(ShaderType::kVertex, vertexCode) & CompileShader(ShaderType::kFragment, fragmentCode);
		
		if (!geometryCode.empty())
		{
			bCompileOk &= CompileShader(ShaderType::kGeometry, geometryCode);
		}

		if (!bCompileOk) return;

		glLinkProgram(ShaderProgramID);
		bCompileOk &= CheckCompileResult(ShaderProgramID, ShaderType::kProgram);
		
		if (!bCompileOk) return;
		glDeleteShader(ShaderVertexID);
		glDeleteShader(ShaderFragmentID);
		if (!geometryCode.empty())
		{
			glDeleteShader(ShaderGeometryID);
		}
	}

	void OpenGLShader::LockShader() const
	{
		glUseProgram(ShaderProgramID);
	}

	void OpenGLShader::UnlockShader() const
	{
		glUseProgram(0);
	}
	
	GW_BOOL OpenGLShader::RecursiveLoadShaderFile(const GW_CHAR* glslShaderFilePath, std::string& shaderCode)
	{
		std::ifstream shaderFile(glslShaderFilePath);
	
		if (shaderFile.is_open())
		{
			std::string shaderLine;
			while (getline(shaderFile, shaderLine))
			{
				shaderCode += "\n";
				if (std::size_t pos = shaderLine.find(ShaderPragmaInclude) != std::string::npos)
				{
					std::string include_file_path = shaderLine.substr(pos + 16, pos + shaderLine.size() - 19);
					RecursiveLoadShaderFile(include_file_path.c_str(), shaderCode);
				}
				else
				{
					shaderCode += shaderLine;
				}
			}
			shaderFile.close();
		}
		else
		{
			GAMEWORLD_CORE_ERROR
			(
				"OpenGLShader::RecursiveLoadShaderFile::cannot load shader file!\n\tShader File : {0}", glslShaderFilePath
			);
			return false;
		}

		return true;
	}

	GW_BOOL OpenGLShader::LoadShaderFile(const GW_CHAR* shaderFilePath, ShaderType type)
	{
		std::string shaderCode("");
		if (!RecursiveLoadShaderFile(shaderFilePath, shaderCode))
		{
			GAMEWORLD_CORE_ERROR
			(
				"OpenGLShader::LoadShaderFile::cannot load shader file!\n\tShader Type : {0}\n\tShader File : {1}",
				ShaderTool::ShaderTypeToString(type), shaderFilePath
			);
		}
		return CompileShader(type, shaderCode);
	}

	GW_BOOL OpenGLShader::CompileShader(ShaderType type, const std::string& shader_code)
	{
		GW_BOOL bCompileSuccess = false;
		const GLchar* code = shader_code.c_str();
		switch (type)
		{
		case ShaderType::kVertex:
		{
			ShaderVertexID = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(ShaderVertexID, 1, &code, NULL);
			glCompileShader(ShaderVertexID);
			bCompileSuccess = CheckCompileResult(ShaderVertexID, type);
			glAttachShader(ShaderProgramID, ShaderVertexID);
			break;
		}
		case ShaderType::kFragment:
		{
			ShaderFragmentID = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(ShaderFragmentID, 1, &code, NULL);
			glCompileShader(ShaderFragmentID);
			bCompileSuccess = CheckCompileResult(ShaderFragmentID, type);
			glAttachShader(ShaderProgramID, ShaderFragmentID);
			break;
		}
		case ShaderType::kGeometry:
		{
			ShaderGeometryID = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(ShaderGeometryID, 1, &code, NULL);
			glCompileShader(ShaderGeometryID);
			bCompileSuccess = CheckCompileResult(ShaderGeometryID, type);
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

	GW_BOOL OpenGLShader::CheckCompileResult(GW_UINT32 shader, ShaderType type)
	{
		int success;
		char infoLog[1024];
		if (type != ShaderType::kProgram)
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