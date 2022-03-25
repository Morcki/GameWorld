#include "Layer2D.h"


Game2DLayer::Game2DLayer(const std::string& name /*= "Game2DLayer"*/)
	: Layer(name)
{
	camera_controller_ = CreateScope<Camera2DOrthoController>(Application::GetInst().GetWindow().GetAspectRatio(), true);
	shader_vertex_array_ = RenderArray::CreateRenderArray();
	squad_shader_vertex_array_ = RenderArray::CreateRenderArray();

	{
		GW_FLOAT32 vertices[3 * 7] =
		{
			-0.25f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			-0.25f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
			 0.28f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		};

		auto vertex_buffer = VertexBuffer::CreateVertexBuffer(vertices, sizeof(vertices));
		vertex_buffer->SetLayout
		({
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"},
			});
		shader_vertex_array_->AddVertexBuffer(vertex_buffer);

		GW_UINT32 indices[3] = { 0, 1, 2 };
		auto index_buffer = IndexBuffer::CreateIndexBuffer(indices, sizeof(indices) / sizeof(GW_UINT32));
		shader_vertex_array_->SetIndexBuffer(index_buffer);

		shader_program_ = ShaderBase::CreateShaderBase();

		shader_program_->LinkShaderFile
		(
			"Shader/vertex/test.vs",
			"Shader/fragment/test.fs"
		);
		shader_program_->LockShader();
	}

	{
		GW_FLOAT32 squad_vertices[4 * 5] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		};
		auto squad_vertex_buffer = VertexBuffer::CreateVertexBuffer(squad_vertices, sizeof(squad_vertices));
		squad_vertex_buffer->SetLayout
		({
			{ShaderDataType::Float3, "aPosition"},
			{ShaderDataType::Float2, "aTexCoord"},
			});
		squad_shader_vertex_array_->AddVertexBuffer(squad_vertex_buffer);
		GW_UINT32 squad_indices[] = { 0, 1, 2, 1, 2, 3 };
		auto squad_index_buffer = IndexBuffer::CreateIndexBuffer(squad_indices, sizeof(squad_indices) / sizeof(GW_UINT32));
		squad_shader_vertex_array_->SetIndexBuffer(squad_index_buffer);

		squad_shader_program_ = ShaderBase::CreateShaderBase();

		squad_shader_program_->LinkShaderFile
		(
			"Shader/vertex/squad.vs",
			"Shader/fragment/squad.fs"
		);
		squad_shader_program_->LockShader();
	}

	texture_shader_program_ = ShaderBase::CreateShaderBase();
	texture_shader_program_->LinkShaderFile
	(
		"Shader/vertex/texture.vs",
		"Shader/fragment/texture.fs"
	);
	texture_shader_program_->LockShader();

	texture_bg_img_ = Texture2D::CreateTexture2D("Assets/Texture/Image2D/Checkerboard.png");
	texture_ = Texture2D::CreateTexture2D("Assets/Texture/Image2D/awesomeface.png");

	texture_shader_program_->LockShader();
	ShaderTool::SetIntUniform(texture_shader_program_->GetProgramID(), "uTexture", 0);
}

Game2DLayer::~Game2DLayer()
{

}

void Game2DLayer::OnUpdate()
{
	camera_controller_->TickUpdate();

	for (GW_UINT32 x = 0; x < 25; x++)
	{
		for (GW_UINT32 y = 0; y < 25; y++)
		{
			glm::vec3 color = { squad_color.x, squad_color.y, squad_color.z };
			glm::vec3 trans = { x * 1.1, y * 1.1, 0.0f };
			if (x % 2 == 0)
			{
				color = glm::vec3(1.0f) - color;
			}

			RenderPass(squad_shader_program_)
				.begin()
				.next([&]()
					{
						ShaderTool::SetVec3Uniform(squad_shader_program_->GetProgramID(), "uTranslateVec", trans);
						ShaderTool::SetMat4Uniform(squad_shader_program_->GetProgramID(), "uVPmat", camera_controller_->GetCamera().GetViewProjectionMatrix());
						ShaderTool::SetVec3Uniform(squad_shader_program_->GetProgramID(), "uColor", color.x, color.y, color.z);
					})
				.draw(squad_shader_vertex_array_)
				.end();
		}
	}

	RenderPass(texture_shader_program_)
		.begin()
		.next([&]()
			{
				texture_bg_img_->Attach();
				ShaderTool::SetVec3Uniform(texture_shader_program_->GetProgramID(), "uTranslateVec", glm::vec3(0.0f));
				ShaderTool::SetMat4Uniform(texture_shader_program_->GetProgramID(), "uVPmat", camera_controller_->GetCamera().GetViewProjectionMatrix());
			})
		.draw(squad_shader_vertex_array_)
		.end();

	RenderPass(texture_shader_program_)
		.begin()
		.next([&]()
			{
				texture_->Attach();
				ShaderTool::SetVec3Uniform(texture_shader_program_->GetProgramID(), "uTranslateVec", glm::vec3(0.0f));
				ShaderTool::SetMat4Uniform(texture_shader_program_->GetProgramID(), "uVPmat", camera_controller_->GetCamera().GetViewProjectionMatrix());
			})
		.draw(squad_shader_vertex_array_)
		.end();


    RenderPass(shader_program_)
		.begin()
		.next([&]()
			{
				ShaderTool::SetVec3Uniform(shader_program_->GetProgramID(), "uTranslateVec", glm::vec3(-0.5f, 0.5f, 0.0f));
				ShaderTool::SetMat4Uniform(shader_program_->GetProgramID(), "uVPmat", camera_controller_->GetCamera().GetViewProjectionMatrix());
			})
		.draw(shader_vertex_array_)
		.end();
}

void Game2DLayer::OnImGuiRender()
{
	ImGui::Begin("ColorEdit Tool");

	// Edit a color (stored as ~4 floats)
	//const GW_FLOAT32* background_color = GameWorld::Application::GetInst().GetBackgroundColor();
	//GW_FLOAT32 tmp_color[4] = { background_color[0], background_color[1], background_color[2], background_color[3] };
	ImGui::ColorEdit4("Color", &squad_color[0]);

	ImGui::End();
}

void Game2DLayer::OnEvent(GameWorld::Event& event)
{
	camera_controller_->OnEvent(event);
	if (event.GetEventType() == GameWorld::EventType::KeyPressed)
	{
		GameWorld::KeyPressedEvent& e = (GameWorld::KeyPressedEvent&) event;
		GAMEWORLD_INFO("For Test Layer : {0}", (char)e.GetKeyCode());
	}
}
