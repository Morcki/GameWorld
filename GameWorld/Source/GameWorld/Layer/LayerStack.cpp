#include  <PrecompiledHeader.h>

#include "LayerStack.h"

namespace GameWorld {

	LayerStack::~LayerStack()
	{
		for (Layer* layer : layer_vec_)
		{
			layer->OnDetach();
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		layer_vec_.emplace(layer_vec_.begin() + layer_insert_index_, layer);
		layer_insert_index_++;
		layer->OnAttach();
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		layer_vec_.emplace_back(overlay);
		overlay->OnAttach();
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(layer_vec_.begin(), layer_vec_.begin() + layer_insert_index_, layer);
		if (it != layer_vec_.begin() + layer_insert_index_)
		{
			layer->OnDetach();
			layer_vec_.erase(it);
			layer_insert_index_--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(layer_vec_.begin() + layer_insert_index_, layer_vec_.end(), overlay);
		if (it != layer_vec_.end())
		{
			overlay->OnDetach();
			layer_vec_.erase(it);
		}
	}

}