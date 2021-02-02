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
		for (auto entity : m_Entities)
			delete entity;
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
			TransformComponent& tc = m_Registry.get<TransformComponent>(entity);
			if (m_Registry.has<CameraComponent>(entity))
			{
				CameraComponent& cc = m_Registry.get<CameraComponent>(entity);

				cc.Camera.SetCenter(tc.Position);
				cc.Camera.SetRotation(tc.Rotation);
			}
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

	Entity* Scene::CreateEntity(std::string name)
	{
		Entity* entity = new Entity(m_Registry.create(), this );
		entity->AddComponent<TransformComponent>();
		entity->AddComponent<TagComponent>();
		auto& tag = entity->GetComponent<TagComponent>();
		if (name.empty())
		{
			tag.Tag = "Entity";
		}
		else
		{
			tag.Tag = name;
		}
		m_Entities.push_back(entity);
		std::cout << entity << std::endl;
		return entity;
	}

	void Scene::DestroyEntity(Entity entity)
	{
		//auto it = std::find(m_Entities.begin(), m_Entities.end() - 1, &entity);
		//std::cout << &entity << std::endl;
		//m_Entities.erase(it); // TODO : DESTROYS REAL ENTITY IN MEMORY!
		m_Registry.destroy(entity);
	}

	template<typename T>
	bool Scene::OnComponentAdded(Entity entity, T& component)
	{
		static_assert(false);
	}

	template<>
	bool Scene::OnComponentAdded<TagComponent>(Entity entity, TagComponent& component)
	{
		return true;
	}

	template<>
	bool Scene::OnComponentAdded<TransformComponent>(Entity entity, TransformComponent& component)
	{
		return true;
	}

	template<>
	bool Scene::OnComponentAdded<ColorComponent>(Entity entity, ColorComponent& component)
	{
		return true;
	}

	template<>
	bool Scene::OnComponentAdded<RectangleCOmponent>(Entity entity, RectangleCOmponent& component)
	{
		return true;
	}

	template<>
	bool Scene::OnComponentAdded<SpriteComponent>(Entity entity, SpriteComponent& component)
	{
		return true;
	}

	template<>
	bool Scene::OnComponentAdded<NativeScriptComponent>(Entity entity, NativeScriptComponent& component)
	{
		return true;
	}

	template<>
	bool Scene::OnComponentAdded<CameraComponent>(Entity entity, CameraComponent& component)
	{
		return true;
	}
}