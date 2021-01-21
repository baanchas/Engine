#pragma once


namespace Engine {

	class Entity
	{
	public:
		Entity();
		virtual ~Entity();

		virtual void Render(sf::RenderTarget& rt) {}
		virtual void Update(float& ts) {}
	protected:
		std::string m_Name;
	};

}