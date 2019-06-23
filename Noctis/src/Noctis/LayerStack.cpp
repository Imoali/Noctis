#include "ntpch.h"
#include "LayerStack.h"

namespace Noctis {

	LayerStack::LayerStack()
	{
		m_LayerInsert = m_Layers.begin();
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers) {
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer) {
		m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
		layer->OnAttach();
	}

	void LayerStack::PopLayer(Layer* layer) {
		auto it = std::find(begin(), end(), layer);
		if (it != end()) {
			m_Layers.erase(it);
			m_LayerInsert--;
			layer->OnDetach();
		}
	}

	void LayerStack::PushOverlay(Layer* overlay){
		m_Layers.emplace_back(overlay);
		overlay->OnAttach();
	}

	void LayerStack::PopOverlay(Layer* overlay){
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != end()) {
			m_Layers.erase(it);
			overlay->OnDetach();
		}
	}

}