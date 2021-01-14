#include "enpch.h"
#include "LayerStack.h"

namespace Engine {

	LayerStack::LayerStack()
	{
	}

	LayerStack::~LayerStack()
	{
		for (auto it : m_Layers)
		{
			delete it;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.emplace(begin() + m_LastIndex, layer);
		m_LastIndex++;
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);

		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_LastIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
	}

}