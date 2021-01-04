#include "Sennet/Pch.hpp"
#include "Sennet/Scene/Entity.hpp"

namespace Sennet
{

Entity::Entity(entt::entity handle, Scene* scene)
	: m_EntityHandle(handle), m_Scene(scene)
{
}

}
