#include "Layer3D.h"

#include "GameWorld.h"

Game3DLayer::Game3DLayer(const std::string& name /*= "Game2DLayer"*/)
	: Layer(name)
{
	camera_ = CreateRef<GCameraEditor>();

	const std::array<std::string, 6> faces1 =
	{
		"Assets/Texture/Cube3D/BlueSunset/Epic_BlueSunset_Cam_2_Left+X.png",
		"Assets/Texture/Cube3D/BlueSunset/Epic_BlueSunset_Cam_3_Right-X.png",
		"Assets/Texture/Cube3D/BlueSunset/Epic_BlueSunset_Cam_4_Up+Y.png",
		"Assets/Texture/Cube3D/BlueSunset/Epic_BlueSunset_Cam_5_Down-Y.png",
		"Assets/Texture/Cube3D/BlueSunset/Epic_BlueSunset_Cam_0_Front+Z.png",
		"Assets/Texture/Cube3D/BlueSunset/Epic_BlueSunset_Cam_1_Back-Z.png",
		//"Assets/Texture/Cube3D/GloriousPink/Epic_GloriousPink_Cam_2_Left+X.png",
		//"Assets/Texture/Cube3D/GloriousPink/Epic_GloriousPink_Cam_3_Right-X.png",
		//"Assets/Texture/Cube3D/GloriousPink/Epic_GloriousPink_Cam_4_Up+Y.png",
		//"Assets/Texture/Cube3D/GloriousPink/Epic_GloriousPink_Cam_5_Down-Y.png",
		//"Assets/Texture/Cube3D/GloriousPink/Epic_GloriousPink_Cam_0_Front+Z.png",
		//"Assets/Texture/Cube3D/GloriousPink/Epic_GloriousPink_Cam_1_Back-Z.png",
		//"Assets/Texture/Cube3D/Template2/pos-x.jpg",
		//"Assets/Texture/Cube3D/Template2/neg-x.jpg",
		//"Assets/Texture/Cube3D/Template2/pos-y.jpg",
		//"Assets/Texture/Cube3D/Template2/neg-y.jpg",
		//"Assets/Texture/Cube3D/Template2/pos-z.jpg",
		//"Assets/Texture/Cube3D/Template2/neg-z.jpg",
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
}

Game3DLayer::~Game3DLayer()
{
	
}

void Game3DLayer::OnUpdate()
{
	camera_->TickUpdate();
	
	if (InputSystem::IsKeyPressed(Key::C))
	{
		skybox_1_->SetTexture
		({
			"Assets/Texture/Cube3D/GloriousPink/Epic_GloriousPink_Cam_2_Left+X.png",
			"Assets/Texture/Cube3D/GloriousPink/Epic_GloriousPink_Cam_3_Right-X.png",
			"Assets/Texture/Cube3D/GloriousPink/Epic_GloriousPink_Cam_4_Up+Y.png",
			"Assets/Texture/Cube3D/GloriousPink/Epic_GloriousPink_Cam_5_Down-Y.png",
			"Assets/Texture/Cube3D/GloriousPink/Epic_GloriousPink_Cam_0_Front+Z.png",
			"Assets/Texture/Cube3D/GloriousPink/Epic_GloriousPink_Cam_1_Back-Z.png",
		});
	}

	if (InputSystem::IsKeyPressed(Key::P))
	{
		camera_->GetProjectionMode() == EProjectionMode::kPerspective ?
			camera_->UpdateProjectionMode(EProjectionMode::kOrtho)
			: camera_->UpdateProjectionMode(EProjectionMode::kPerspective);
	}
	skybox_1_->TickUpdate(camera_);

	cube_1_->TickUpdate(camera_);
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

	ImGui::Begin("Cube Edit Tool");
	if (ImGui::TreeNode("Cube Transform"))
	{
		transform_edit = cube_1_->GetTransform();
		ImGui::DragFloat3(edit_intro[0], &transform_edit.m_position[0], 0.05f);

		auto angle = glm::eulerAngles(transform_edit.m_rotation);
		ImGui::DragFloat3(edit_intro[1], &angle[0], 0.05f);
		transform_edit.m_rotation = angle;

		ImGui::DragFloat3(edit_intro[2], &transform_edit.m_scale[0], 0.05f);

		cube_1_->SetTransform(transform_edit);
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Cube Color"))
	{
		color_edit = cube_1_->GetColor();
		ImGui::ColorEdit4("Color", &color_edit[0]);
		cube_1_->SetColor(color_edit);

		ImGui::TreePop();
	}
	ImGui::End();
}

void Game3DLayer::OnEvent(Event& event)
{
	camera_->OnEvent(event);
	//if (event.GetEventType() == GameWorld::EventType::KeyPressed)
	//{
	//	GameWorld::KeyPressedEvent& e = (GameWorld::KeyPressedEvent&) event;
	//	GAMEWORLD_INFO("For Test Layer : {0}", (char)e.GetKeyCode());
	//}
}
