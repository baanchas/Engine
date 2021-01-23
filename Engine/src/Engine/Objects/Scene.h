#pragma once

#include "Engine/Components/Components.h"


#include "entt.hpp"

namespace Engine {

	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity();

		void OnUpdate(float& ts);
		void Render(sf::RenderTarget& rt);


	private:
		entt::registry m_Registry;

		friend class Entity;
	};

}
