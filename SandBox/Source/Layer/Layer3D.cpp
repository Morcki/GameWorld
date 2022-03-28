#include "Layer3D.h"

#include "GameWorld.h"

Game3DLayer::Game3DLayer(const std::string& name /*= "Game2DLayer"*/)
	: Layer(name)
{
	camera_cto_ = CreateRef<CameraPerspController>();

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
	const std::array<std::string, 6> faces2 =
	{
		"Assets/Texture/Cube3D/AnotherPlanet/AllSky_Space_AnotherPlanet_Cam_2_Left+X.png",
		"Assets/Texture/Cube3D/AnotherPlanet/AllSky_Space_AnotherPlanet_Cam_3_Right-X.png",
		"Assets/Texture/Cube3D/AnotherPlanet/AllSky_Space_AnotherPlanet_Cam_4_Up+Y.png",
		"Assets/Texture/Cube3D/AnotherPlanet/AllSky_Space_AnotherPlanet_Cam_5_Down-Y.png",
		"Assets/Texture/Cube3D/AnotherPlanet/AllSky_Space_AnotherPlanet_Cam_0_Front+Z.png",
		"Assets/Texture/Cube3D/AnotherPlanet/AllSky_Space_AnotherPlanet_Cam_1_Back-Z.png",
	};
	skybox_1_ = CreateRef<SkyboxMaterial>(camera_cto_, faces1);
	skybox_2_ = CreateRef<SkyboxMaterial>(camera_cto_, faces2);
}

Game3DLayer::~Game3DLayer()
{
	
}

void Game3DLayer::OnUpdate()
{
	camera_cto_->TickUpdate();
	
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

	if (InputSystem::IsKeyPressed(Key::Space))
	{
		skybox_2_->TickUpdate();
	}
	else
	{
		skybox_1_->TickUpdate();
	}
	
}

void Game3DLayer::OnImGuiRender()
{
	ImGui::Begin("ColorEdit Tool");

	// Edit a color (stored as ~4 floats)
	//const GW_FLOAT32* background_color = GameWorld::Application::GetInst().GetBackgroundColor();
	//GW_FLOAT32 tmp_color[4] = { background_color[0], background_color[1], background_color[2], background_color[3] };
	static GW_FLOAT32 squad_color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	ImGui::ColorEdit4("Color", squad_color);

	ImGui::End();
}

void Game3DLayer::OnEvent(Event& event)
{
	camera_cto_->OnEvent(event);
	if (event.GetEventType() == GameWorld::EventType::KeyPressed)
	{
		GameWorld::KeyPressedEvent& e = (GameWorld::KeyPressedEvent&) event;
		GAMEWORLD_INFO("For Test Layer : {0}", (char)e.GetKeyCode());
	}
}
