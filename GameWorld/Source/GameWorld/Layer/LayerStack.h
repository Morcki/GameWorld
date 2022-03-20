#pragma once
#include <vector>

#include "Layer.h"
#include "GameWorld/Core/Core.h"

namespace GameWorld {

	class LayerStack
	{
	public:
		LayerStack() = default;
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin()                      { return layer_vec_.begin(); }
		std::vector<Layer*>::iterator end()                        { return layer_vec_.end(); }
		std::vector<Layer*>::reverse_iterator rbegin()             { return layer_vec_.rbegin(); }
		std::vector<Layer*>::reverse_iterator rend()               { return layer_vec_.rend(); }

		std::vector<Layer*>::const_iterator begin()          const { return layer_vec_.begin(); }
		std::vector<Layer*>::const_iterator end()	         const { return layer_vec_.end(); }
		std::vector<Layer*>::const_reverse_iterator rbegin() const { return layer_vec_.rbegin(); }
		std::vector<Layer*>::const_reverse_iterator rend()   const { return layer_vec_.rend(); }
	private:
		std::vector<Layer*> layer_vec_;
		unsigned int layer_insert_index_ = 0;
	};

}