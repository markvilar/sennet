#pragma once

#include <entt/entt.hpp>

namespace Sennet
{

class Entity;

class Scene
{
public:
	Scene();
	~Scene();

	Entity CreateEntity(const std::string& name = std::string()); 
	void DestroyEntity(Entity entity);

private:
	template<typename T>
	void OnComponentAdded(Entity entity, T& component);

private:
	entt::registry m_Registry;
	uint32_t m_ViewportWidth = 0;
	uint32_t m_ViewportHeight = 0;

	friend class Entity;
};

}
