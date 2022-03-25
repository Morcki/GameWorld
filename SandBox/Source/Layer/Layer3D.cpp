#include "Layer3D.h"

#include "GameWorld.h"

Game3DLayer::Game3DLayer(const std::string& name /*= "Game2DLayer"*/)
	: Layer(name)
{
	camera_cto_ = CreateRef<CameraPerspController>();

	skybox_vao_ = RenderArray::CreateRenderArray();

	skybox_texture_ = TextureCube3D::CreateTextureCube3D
	({
		"Assets/Texture/Cube3D/Template1/right.jpg",
		"Assets/Texture/Cube3D/Template1/left.jpg",
		"Assets/Texture/Cube3D/Template1/top.jpg",
		"Assets/Texture/Cube3D/Template1/bottom.jpg",
		"Assets/Texture/Cube3D/Template1/front.jpg",
		"Assets/Texture/Cube3D/Template1/back.jpg",
	});

	GW_FLOAT32 skybox_vertices[] = 
	{
		// positions          
		-1.0f,  1.0f, -1.0f,   -1.0f, -1.0f, -1.0f,    1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,    1.0f,  1.0f, -1.0f,   -1.0f,  1.0f, -1.0f,
		
		-1.0f, -1.0f,  1.0f,   -1.0f, -1.0f, -1.0f,   -1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,   -1.0f,  1.0f,  1.0f,   -1.0f, -1.0f,  1.0f,
		
		 1.0f, -1.0f, -1.0f,    1.0f, -1.0f,  1.0f,    1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,    1.0f,  1.0f, -1.0f,    1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,   -1.0f,  1.0f,  1.0f,    1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,    1.0f, -1.0f,  1.0f,   -1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,    1.0f,  1.0f, -1.0f,    1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,   -1.0f,  1.0f,  1.0f,   -1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,   -1.0f, -1.0f,  1.0f,    1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,   -1.0f, -1.0f,  1.0f,    1.0f, -1.0f,  1.0f
	};

	auto skybox_vbo = VertexBuffer::CreateVertexBuffer(skybox_vertices, sizeof(skybox_vertices));
	skybox_vbo->SetLayout
	({
		{ ShaderDataType::Float3, "aPos" },
	});
	skybox_vao_->AddVertexBuffer(skybox_vbo);

	shader_3d_program_ = ShaderBase::CreateShaderBase();
	shader_3d_program_->LinkShaderFile
	(
		"Shader/vertex/skybox_temp1.vert",
		"Shader/fragment/skybox_temp1.frag"
	);
	RenderPass(shader_3d_program_)
		.begin()
		.next([&]()
		{
			ShaderTool::SetIntUniform(shader_3d_program_->GetProgramID(), "skybox", 0);
		});
}

Game3DLayer::~Game3DLayer()
{
	
}

void Game3DLayer::OnUpdate()
{
	camera_cto_->TickUpdate();
	RenderPass(shader_3d_program_)
		.begin()
		.next([&]()
			{
				RenderCommand::SetDepthMask(false);
				RenderCommand::SetDepthFunc(ShaderCmpFunc::kLEqual);
			})
		.next([&]()
			{
				skybox_texture_->Attach();
				skybox_vao_->Bind();
				ShaderTool::SetMat4Uniform(shader_3d_program_->GetProgramID(), "uView", camera_cto_->GetCamera().GetViewMatrixWithoutTranslate());
				ShaderTool::SetMat4Uniform(shader_3d_program_->GetProgramID(), "uProj", camera_cto_->GetCamera().GetProjectionMatrix());
				//ShaderTool::SetMat4Uniform(shader_3d_program_->GetProgramID(), "uView", camera_cto_->GetCamera().GetViewProjectionMatrix());
			})
		.next([&]()
			{
				RenderCommand::DrawArrays(36);
			})
		.end([&]()
			{
				RenderCommand::SetDepthMask(true);
				RenderCommand::SetDepthFunc(ShaderCmpFunc::kLess);
			});
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
