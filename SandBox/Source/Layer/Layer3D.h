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
	Ref<GCubeInstance> cube_1;
	Ref<GSphereInstance> sphere_1;
	Ref<GSphereInstance> sphere_2;
};