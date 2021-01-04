#include "Sennet/Pch.hpp"
#include "Sennet/Scene/Scene.hpp"

#include <glm/glm.hpp>

#include "Sennet/Scene/Components.hpp"
#include "Sennet/Scene/Entity.hpp"

namespace Sennet
{

Scene::Scene()
{
}

Scene::~Scene()
{
}

Entity Scene::CreateEntity(const std::string& name)
{
	Entity entity = { m_Registry.create(), this };
	entity.AddComponent<TransformComponent>();
	auto& tag = entity.AddComponent<TagComponent>();
	tag.Tag = name.empty() ? "Entity" : name;
	return entity;
}

void Scene::DestroyEntity(Entity entity)
{
	m_Registry.destroy(entity);
}

template<typename T>
void Scene::OnComponentAdded(Entity entity, T& component)
{
	static_assert(false);
}

template<>
void Scene::OnComponentAdded<TagComponent>(Entity entity, 
	TagComponent& component)
{
}

template<>
void Scene::OnComponentAdded<TransformComponent>(Entity entity, 
	TransformComponent& component)
{
}

}
