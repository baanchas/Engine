#pragma once
#include "Entity.h"

namespace Engine {

	class ScriptableEntity
	{
	public:
		virtual ~ScriptableEntity() {}


		template<typename T>
		T& GetComponent()
		{
			return m_Entity.GetComponent<T>();
		}
	protected:
		virtual void OnUpdate(float ts) {};
		virtual void OnCreate() {};
		virtual void OnDestroy() {};
	private:
		Entity m_Entity;
		friend class Scene;
	};

}