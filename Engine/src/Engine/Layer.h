#pragma once

namespace Engine {

	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnEvent(sf::Event& event) = 0;
		virtual void OnUpdate(float& ts) = 0;
		virtual void Render(sf::RenderTarget& rt) = 0;


		inline const std::string& GetName() const
		{
			return m_Name;
		}

	protected:
		std::string m_Name;
	};

}
