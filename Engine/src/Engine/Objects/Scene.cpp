#include "enpch.h"
#include "Scene.h"


#include "Entity.h"

namespace Engine {

	Scene::Scene()
	{

	}

	Scene::~Scene()
	{

	}

	void Scene::OnUpdate(float& ts)
	{
		auto groupTCRC = m_Registry.group<TransformComponent>(entt::get<RectangleCOmponent>);
		for (auto entity : groupTCRC)
		{
			auto [transform, shape] = groupTCRC.get<TransformComponent, RectangleCOmponent>(entity);

			shape.rect.setScale(transform.Scale);
			shape.rect.setPosition(transform.GetPosition());
			//shape.rect.setFillColor(sf::Color::Red);
		}

		auto groupTCCC = m_Registry.group<RectangleCOmponent>(entt::get<ColorComponent>);
		for (auto entity : groupTCCC)
		{
			auto [shape, color] = groupTCCC.get<RectangleCOmponent, ColorComponent>(entity);

			shape.rect.setFillColor(color.Color);
		}

	}

	void Scene::Render(sf::RenderTarget& rt)
	{
		auto group = m_Registry.group<TransformComponent>(entt::get<RectangleCOmponent>);
		for (auto entity : group)
		{
			auto [transform, shape] = group.get<TransformComponent, RectangleCOmponent>(entity);

			rt.draw(shape.rect);
		}
	}

	Entity Scene::CreateEntity()
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		return entity;
	}
}