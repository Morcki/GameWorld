#pragma once
#include <GameWorld.h>

#include "imgui/imgui.h"
#include "glm/glm.hpp"

using namespace GameWorld;

class Game2DLayer : public GameWorld::Layer
{
public:
	Game2DLayer(const std::string& name = "Game2DLayer");
	virtual	~Game2DLayer();
	

	void OnUpdate() override;

	void OnImGuiRender() override;

	void OnEvent(GameWorld::Event& event) override;

private:
	Ref<ShaderBase>      shader_program_;
	Ref<RenderArray>     shader_vertex_array_;
	Ref<ShaderBase>      squad_shader_program_;
	Ref<RenderArray>     squad_shader_vertex_array_;
	Ref<ShaderBase>      texture_shader_program_;
	Ref<Texture2D>       texture_bg_img_;
	Ref<Texture2D>       texture_;
	Scope<GCamera2D>     camera_;

	glm::vec4 squad_color = { 0.0f, 0.0f, 1.0f, 1.0f };
};