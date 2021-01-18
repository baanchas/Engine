#pragma once

namespace Engine {

	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnEvent(sf::Event& event) {};
		virtual void OnUpdate(float& time) {};
		virtual void Render(sf::RenderTarget& rt) {};
		virtual void OnImGuiRender(sf::RenderTarget& rt) {};

		inline const std::string& GetName() const
		{
			return m_Name;
		}

	protected:
		std::string m_Name;
	};

}
