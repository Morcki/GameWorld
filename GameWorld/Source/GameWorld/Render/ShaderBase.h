#pragma once

#include <string>

#include "ShaderTool.h"

namespace GameWorld
{
	
	class ShaderBase
	{
	public:
		
		ShaderBase();
		~ShaderBase();

		inline GW_UINT32 GetProgramID() { return ShaderProgramID; };

		virtual void LinkShaderFile(const GW_CHAR* vertexPath, const GW_CHAR* fragmentPath, const GW_CHAR* geometryPath = nullptr);

		virtual void UseShader();
		virtual void DeleteShader();

	private:
		GW_BOOL LoadShaderFile(const GW_CHAR* shaderFilePath, ShaderType type);
		GW_BOOL CheckShaderCompile(GW_UINT32 shader, ShaderType type);

	private:
		GW_UINT32 ShaderProgramID;
		GW_UINT32 ShaderVertexID;
		GW_UINT32 ShaderFragmentID;
		GW_UINT32 ShaderGeometryID;
	};

}
