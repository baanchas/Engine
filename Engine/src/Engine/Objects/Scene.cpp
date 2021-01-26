#include "enpch.h"
#include "Scene.h"


#include "Entity.h"

namespace Engine {

	Scene::Scene()
	{
		ENGINE_INFO("Scene loaded!");
	}

	Scene::~Scene()
	{

	}

	void Scene::OnUpdate(float& ts)
	{

		auto viewRCTC = m_Registry.view<RectangleCOmponent, TransformComponent>();
		for (auto entity : viewRCTC)
		{
			RectangleCOmponent& rc = m_Registry.get<RectangleCOmponent>(entity);
			TransformComponent& tc = m_Registry.get<TransformComponent>(entity);

			rc.rect.setScale(tc.Scale);
			rc.rect.setPosition(tc.GetPosition());

			if (m_Registry.has<ColorComponent>(entity))
			{
				ColorComponent& cc = m_Registry.get<ColorComponent>(entity);
				rc.rect.setFillColor(cc.Color);
			}
		}

		auto viewSCTC = m_Registry.view<SpriteComponent, TransformComponent>();
		for (auto entity : viewSCTC)
		{
			SpriteComponent& sc = m_Registry.get<SpriteComponent>(entity);
			TransformComponent& tc = m_Registry.get<TransformComponent>(entity);
			sc.Sprite.setScale(tc.Scale);
			sc.Sprite.setPosition(tc.GetPosition());
		}

/*		auto viewSCTC = m_Registry.view<SpriteComponent, TransformComponent>();
		for (auto entity : viewSCTC)
		{
			SpriteComponent& sc = m_Registry.get<SpriteComponent>(entity);
			TransformComponent& tc = m_Registry.get<TransformComponent>(entity);
			sc.Sprite.setScale(tc.Scale);
			sc.Sprite.setPosition(tc.GetPosition());
		}*/
	}

	void Scene::Render(sf::RenderTarget& rt)
	{
		//bool render = false;

		auto view = m_Registry.view<RectangleCOmponent>();
		for (auto entity : view)
		{
			RectangleCOmponent& rc = m_Registry.get<RectangleCOmponent>(entity);
			rt.draw(rc.rect);
		}
		
		auto viewSprite = m_Registry.view<SpriteComponent>();
		for (auto entity : viewSprite)
		{
			SpriteComponent& sc = m_Registry.get<SpriteComponent>(entity);
			rt.draw(sc.Sprite);
		}
	}

	Entity Scene::CreateEntity()
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		return entity;
	}
}