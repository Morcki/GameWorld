#pragma once

#include "GameWorld/Core/Core.h"
#include "GameWorld/Core/GTimeSystem.h"
#include "GameWorld/Events/Event.h"

namespace GameWorld {

	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		const std::string& GetName() const { return layer_name_; }
	protected:
		std::string layer_name_;
	};

}