#include "Layer3D.h"

#include "GameWorld.h"

Game3DLayer::Game3DLayer(const std::string& name /*= "Game2DLayer"*/)
	: Layer(name)
{

	const std::array<std::string, 6> faces1 =
	{
		"Assets/Texture/Cube3D/BlueSunset/Epic_BlueSunset_Cam_2_Left+X.png",
		"Assets/Texture/Cube3D/BlueSunset/Epic_BlueSunset_Cam_3_Right-X.png",
		"Assets/Texture/Cube3D/BlueSunset/Epic_BlueSunset_Cam_4_Up+Y.png",
		"Assets/Texture/Cube3D/BlueSunset/Epic_BlueSunset_Cam_5_Down-Y.png",
		"Assets/Texture/Cube3D/BlueSunset/Epic_BlueSunset_Cam_0_Front+Z.png",
		"Assets/Texture/Cube3D/BlueSunset/Epic_BlueSunset_Cam_1_Back-Z.png",
	};
	//const std::array<std::string, 6> faces2 =
	//{
	//	"Assets/Texture/Cube3D/AnotherPlanet/AllSky_Space_AnotherPlanet_Cam_2_Left+X.png",
	//	"Assets/Texture/Cube3D/AnotherPlanet/AllSky_Space_AnotherPlanet_Cam_3_Right-X.png",
	//	"Assets/Texture/Cube3D/AnotherPlanet/AllSky_Space_AnotherPlanet_Cam_4_Up+Y.png",
	//	"Assets/Texture/Cube3D/AnotherPlanet/AllSky_Space_AnotherPlanet_Cam_5_Down-Y.png",
	//	"Assets/Texture/Cube3D/AnotherPlanet/AllSky_Space_AnotherPlanet_Cam_0_Front+Z.png",
	//	"Assets/Texture/Cube3D/AnotherPlanet/AllSky_Space_AnotherPlanet_Cam_1_Back-Z.png",
	//};
	skybox_1_ = CreateRef<SkyboxMaterial>(faces1);
	//skybox_2_ = CreateRef<SkyboxMaterial>(faces2);
	cube_1_ = CreateRef<GCube>();

	Application::GetInst().GetSceneManager().SetSkybox(skybox_1_);
	Application::GetInst().GetSceneManager().PlaceGameObject(cube_1_);
}

Game3DLayer::~Game3DLayer()
{
	
}

void Game3DLayer::OnUpdate()
{
	
}

void Game3DLayer::OnImGuiRender()
{
	// Edit a color (stored as ~4 floats)
	//const GW_FLOAT32* background_color = GameWorld::Application::GetInst().GetBackgroundColor();
	//GW_FLOAT32 tmp_color[4] = { background_color[0], background_color[1], background_color[2], background_color[3] };
	static glm::vec4 color_edit;
	static MTransform transform_edit;

	static const GW_INT8 *edit_intro[] =
	{
		"Position",
		"Rotation",
		"Scale   "
	};
	auto directional_light = Application::GetInst().GetSceneManager().GetDirectgionalLight();
	auto ambient_light = Application::GetInst().GetSceneManager().GetAmbientLight();

	ImGui::Begin("Cube Edit Tool");
	if (ImGui::TreeNode("Scene Directional Light"))
	{
		ImGui::DragFloat3("Light Direction", &directional_light.m_direction[0], 0.05f);
		ImGui::ColorEdit3("Light Color", &directional_light.m_color[0]);
		ImGui::ColorEdit3("Ambient Light Color", &ambient_light.m_irradiance[0]);
		ImGui::TreePop();
	}

	Application::GetInst().GetSceneManager().SetDirecionalLight(directional_light);
	Application::GetInst().GetSceneManager().SetAmbientLight(ambient_light);

	if (ImGui::TreeNode("Cube Transform"))
	{
		transform_edit = cube_1_->GetTransform();
		ImGui::DragFloat3(edit_intro[0], &transform_edit.m_position[0], 0.05f);

		auto angle = glm::degrees(glm::eulerAngles(transform_edit.m_rotation));
	
		ImGui::DragFloat3(edit_intro[1], &angle[0], 0.05f);
		transform_edit.m_rotation = glm::radians(angle);

		ImGui::DragFloat3(edit_intro[2], &transform_edit.m_scale[0], 0.05f);

		cube_1_->SetTransform(transform_edit);
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Cube Material"))
	{
		auto cube_material = cube_1_->GetMaterial();
		auto cube_material_constant = cube_material.GetConstant();

		ImGui::ColorEdit4("Cube Base Color", &cube_material_constant.diffuse_albedo[0]);
		ImGui::DragFloat3("Fresnel R0", &cube_material_constant.fresnel_R0[0], 0.001f, 0.0f, 1.0f);
		ImGui::DragFloat("Roughness", &cube_material_constant.roughness, 0.001f, 0.0f, 1.0f);
		
		cube_material.SetConstant(cube_material_constant);
		cube_1_->SetMaterial(cube_material);

		ImGui::TreePop();
	}
	ImGui::End();
}

void Game3DLayer::OnEvent(Event& event)
{
	//if (event.GetEventType() == GameWorld::EventType::KeyPressed)
	//{
	//	GameWorld::KeyPressedEvent& e = (GameWorld::KeyPressedEvent&) event;
	//	GAMEWORLD_INFO("For Test Layer : {0}", (char)e.GetKeyCode());
	//}
}
