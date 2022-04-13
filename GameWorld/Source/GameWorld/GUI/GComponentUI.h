#pragma once

#include "imgui/imgui.h"

#include "GameWorld/Component/GComponent.h"
#include "GameWorld/Core/math/MTransform.h"

namespace GameWorld
{
	constexpr GW_INT8 *edit_intro[] =
	{
		"Position",
		"Rotation",
		"Scale   "
	};

	
	class GComponentUI
	{
	public:

		static void ShowComponentDetails(GComponent& object)
		{
			auto ui_name = object.GetName() + "Edit Tool";
			ImGui::Begin(ui_name.c_str());
			if (ImGui::TreeNode("Transform"))
			{
				auto transform = object.GetTransform();
				ImGui::DragFloat3(edit_intro[0], &transform.m_position[0], 0.05f);

				auto angle = glm::degrees(glm::eulerAngles(transform.m_rotation));

				ImGui::DragFloat3(edit_intro[1], &angle[0], 0.05f);
				transform.m_rotation = glm::radians(angle);

				ImGui::DragFloat3(edit_intro[2], &transform.m_scale[0], 0.05f);

				object.SetTransform(transform);
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("Material"))
			{
				auto material = object.GetMaterial();
				auto material_constant = material.GetConstant();

				ImGui::ColorEdit4("Base Color", &material_constant.diffuse_albedo[0]);
				ImGui::DragFloat("Metallic", &material_constant.metallic, 0.001f, 0.0f, 1.0f);
				ImGui::DragFloat("Roughness", &material_constant.roughness, 0.001f, 0.0f, 1.0f);

				material.SetConstant(material_constant);
				object.SetMaterial(material);

				ImGui::TreePop();
			}
			ImGui::End();
		}



	};
}
