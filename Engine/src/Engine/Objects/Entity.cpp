#include "enpch.h"
#include "Entity.h"

namespace Engine {

	Entity::Entity(entt::entity id, Scene* scene)
		: m_EntityId(id), m_Scene(scene)
	{
	}

	Entity::~Entity()
	{
	}

	

}