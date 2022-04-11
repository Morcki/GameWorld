#pragma once
#include <GameWorld.h>

#include "imgui/imgui.h"
#include "glm/glm.hpp"

using namespace GameWorld;

class Game3DLayer : public Layer
{
public:
	Game3DLayer(const std::string& name = "Game3DLayer");
	virtual ~Game3DLayer() override;
	void OnUpdate() override;
	void OnImGuiRender() override;
	void OnEvent(Event& event) override;

private:
	Ref<SkyboxMaterial> skybox_1_;
	Ref<SkyboxMaterial> skybox_2_;
	Ref<GCube>          cube_1_;
	
};