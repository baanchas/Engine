#include "enpch.h"
#include "Scene.h"
#include "Engine/Components/Components.h"

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
		{
			m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
			{
				if (!nsc.Instance)
				{
					nsc.Instance = nsc.InstantiateFunction();
					nsc.Instance->m_Entity = Entity{ entity, this };
					nsc.Instance->OnCreate();
				}
				//if ()
				nsc.Instance->OnUpdate(ts);
			});
		}

		auto viewRC = m_Registry.view<RectangleCOmponent>();
		for (auto entity : viewRC)
		{
			RectangleCOmponent& rc = m_Registry.get<RectangleCOmponent>(entity);

			rc.rect.setSize(rc.Size);
			rc.SetOrigin();
		}

		auto viewRCTC = m_Registry.view<RectangleCOmponent, TransformComponent>();
		for (auto entity : viewRCTC)
		{
			RectangleCOmponent& rc = m_Registry.get<RectangleCOmponent>(entity);
			TransformComponent& tc = m_Registry.get<TransformComponent>(entity);

			rc.rect.setScale(tc.Scale);
			rc.rect.setPosition(tc.GetPosition());
			rc.rect.setRotation(tc.Rotation);

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

		auto viewCCTC = m_Registry.view<CameraComponent, TransformComponent>();
		for (auto entity : viewCCTC)
		{
			CameraComponent& cc = m_Registry.get<CameraComponent>(entity);
			TransformComponent& tc = m_Registry.get<TransformComponent>(entity);
			cc.Camera.SetCenter(tc.Position);
			cc.Camera.SetRotation(tc.Rotation);
		}
	}

	void Scene::OnScenePLay(float ts)
	{

	}

	void Scene::Render(sf::RenderTarget& rt)
	{
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

	Entity Scene::CreateEntity(std::string name)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		entity.AddComponent<TagComponent>();
		auto& tag = entity.GetComponent<TagComponent>();
		if (name.empty())
		{
			tag.Tag = "Entity";
		}
		else
		{
			tag.Tag = name;
		}
		return entity;
	}
}