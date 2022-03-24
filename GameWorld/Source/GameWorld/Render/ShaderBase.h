#pragma once

#include <string>

#include "ShaderTool.h"

namespace GameWorld
{
	
	class ShaderBase
	{
	public:		
		virtual ~ShaderBase() = default;

		virtual void LinkShaderFile(const GW_CHAR* vertexPath, const GW_CHAR* fragmentPath, const GW_CHAR* geometryPath = nullptr) = 0;

		inline GW_UINT32 GetProgramID() { return ShaderProgramID; };

		virtual void LockShader()   const = 0;
		virtual void UnlockShader() const = 0;

		static Ref<ShaderBase> CreateShaderBase();

	protected:
		GW_UINT32 ShaderProgramID = 0;
	};

}
