#include "Layer3D.h"

#include "GameWorld.h"

Game3DLayer::Game3DLayer(const std::string& name /*= "Game2DLayer"*/)
	: Layer(name)
{
	const std::array<std::string, 6> faces1 =
	{
		"../GameWorld/Assets/Texture/Cube3D/BlueSunset/Epic_BlueSunset_Cam_2_Left+X.png",
		"../GameWorld/Assets/Texture/Cube3D/BlueSunset/Epic_BlueSunset_Cam_3_Right-X.png",
		"../GameWorld/Assets/Texture/Cube3D/BlueSunset/Epic_BlueSunset_Cam_4_Up+Y.png",
		"../GameWorld/Assets/Texture/Cube3D/BlueSunset/Epic_BlueSunset_Cam_5_Down-Y.png",
		"../GameWorld/Assets/Texture/Cube3D/BlueSunset/Epic_BlueSunset_Cam_0_Front+Z.png",
		"../GameWorld/Assets/Texture/Cube3D/BlueSunset/Epic_BlueSunset_Cam_1_Back-Z.png",
	};
	
	//auto skybox = CreateRef<SkyboxMaterial>(faces1);
	cube_1 = CreateRef<GCubeInstance>();
	sphere_1 = CreateRef<GSphereInstance>();
	sphere_2 = CreateRef<GSphereInstance>();
	auto cube_2 = CreateRef<GCubeInstance>();
	////Application::GetInst().GetSceneManager().PlaceSkybox(skybox);
	//
	auto cube2_transform = MTransform();
	cube2_transform.m_position = { -2.5f, -2.5f, 0.2f };
	cube2_transform.m_scale *= 0.2;
	cube_2->SetTransform(cube2_transform);

	auto sphere_1_transform = sphere_1->GetTransform();
	sphere_1_transform.m_position = { 0.0f, 0.0f, 3.0f };
	sphere_1->SetTransform(sphere_1_transform);

	Application::GetInst().GetSceneManager().PlaceGameObject(cube_1);
	Application::GetInst().GetSceneManager().PlaceGameObject(cube_2);
	Application::GetInst().GetSceneManager().PlaceGameObject(sphere_1);
	Application::GetInst().GetSceneManager().PlaceGameObject(sphere_2);
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

	auto directional_light = Application::GetInst().GetSceneManager().GetDirectgionalLight();
	auto ambient_light = Application::GetInst().GetSceneManager().GetAmbientLight();

	ImGui::Begin("Scene Directional Light");
	if (ImGui::TreeNode("Directional Light"))
	{
		ImGui::DragFloat3("Light Direction", &directional_light.m_direction[0], 0.05f);
		ImGui::ColorEdit3("Light Color", &directional_light.m_color[0]);
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Ambient Light"))
	{
		ImGui::ColorEdit3("Ambient Light Color", &ambient_light.m_irradiance[0]);
		ImGui::TreePop();
	}

	Application::GetInst().GetSceneManager().PlaceDirecionalLight(directional_light);
	Application::GetInst().GetSceneManager().PlaceAmbientLight(ambient_light);
	ImGui::End();
	
	GComponentUI::ShowComponentDetails(*sphere_1);
	GComponentUI::ShowComponentDetails(*cube_1);
	GComponentUI::ShowComponentDetails(*sphere_2);
}

void Game3DLayer::OnEvent(Event& event)
{
	//if (event.GetEventType() == GameWorld::EventType::KeyPressed)
	//{
	//	GameWorld::KeyPressedEvent& e = (GameWorld::KeyPressedEvent&) event;
	//	GAMEWORLD_INFO("For Test Layer : {0}", (char)e.GetKeyCode());
	//}
}
