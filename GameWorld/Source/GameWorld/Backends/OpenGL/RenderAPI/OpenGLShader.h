#pragma once

#include "GameWorld/Render/ShaderBase.h"

#include <string>

namespace GameWorld
{
	class OpenGLShader : public ShaderBase
	{
	public:

		OpenGLShader();
		virtual ~OpenGLShader() override;

		//virtual void LinkShaderFile(const GW_CHAR* glslFilePath) override;
		virtual void LinkShaderFile(const GW_CHAR* vertexPath, const GW_CHAR* fragmentPath, const GW_CHAR* geometryPath = nullptr) override;

		virtual void LockShader() const override;
		virtual void UnlockShader() const override;

	private:
		GW_BOOL LoadShaderFile(const GW_CHAR* shaderFilePath, ShaderType type);
		GW_BOOL CompileShader(ShaderType type, const std::string& shader_code);
		GW_BOOL CheckCompileResult(GW_UINT32 shader, ShaderType type);

	private:
		GW_UINT32 ShaderVertexID;
		GW_UINT32 ShaderFragmentID;
		GW_UINT32 ShaderGeometryID;
	};

}
