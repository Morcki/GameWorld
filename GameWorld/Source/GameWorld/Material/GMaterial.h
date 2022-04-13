#pragma once

#include <string>

#include "GameWorld/Core/math/MTransform.h"
#include "GameWorld/Render/ShaderBase.h"

namespace GameWorld
{
	struct MaterialConstant
	{
		glm::vec4  diffuse_albedo{ glm::vec4{1.0f} };
		GW_FLOAT32 metallic { 0.25f };
		GW_FLOAT32 roughness{ 0.25f };
	};

	class GMaterial
	{
	public:
		GMaterial(const std::string& name);
		GMaterial(const std::string& name, MTransform& transform, MaterialConstant& constant);
		virtual ~GMaterial() = default;

		void BindShader(const Ref<ShaderBase>& shader) { m_shader = shader; };
		void SetConstant(const MaterialConstant& constant) { m_constant = constant; };

	public:
		inline const Ref<ShaderBase>&  GetShader() { return m_shader; };
		inline MaterialConstant GetConstant() { return m_constant; };

	protected:
		std::string      m_name;
		MTransform       m_transform{ MTransform() };
		MaterialConstant m_constant{ MaterialConstant() };
		
		Ref<ShaderBase>  m_shader;
	};
}
