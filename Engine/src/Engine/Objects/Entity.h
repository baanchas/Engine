#pragma once


namespace Engine {

	class Entity
	{
	public:
		Entity();
		virtual ~Entity();

		virtual void Render(sf::RenderTarget& rt) = 0;
	protected:
		std::string m_Name;
	};

}