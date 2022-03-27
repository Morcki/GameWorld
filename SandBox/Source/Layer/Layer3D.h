#pragma once
#include <GameWorld.h>

#include "imgui/imgui.h"
#include "glm/glm.hpp"

using namespace GameWorld;

class Game3DLayer : public Layer
{
public:
	Game3DLayer(const std::string& name = "Game2DLayer");
	virtual ~Game3DLayer() override;
	void OnUpdate() override;
	void OnImGuiRender() override;
	void OnEvent(Event& event) override;

private:
	Ref<CameraPerspController> camera_cto_;
	Ref<SkyboxRenderPass> skybox_;
	
};