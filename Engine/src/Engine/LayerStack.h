#pragma once

#include "Layer.h"

namespace Engine {

	class LayerStack
	{
	public:

		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		inline Layer* top() { return m_Layers.back(); }
		inline int GetSize() const { return (int)m_Layers.size(); }

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LastIndex = 0;
	};
}
