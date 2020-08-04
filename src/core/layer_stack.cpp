#include <sennet/core/layer_stack.hpp>

namespace sennet
{

layer_stack::~layer_stack()
{
	for (layer* lay : m_layers)
	{
		lay->on_detach();
		delete lay;
	}
}

void layer_stack::push_layer(layer* lay)
{
	// Layers get pushed into the vector in front of the overlays.
	m_layers.emplace(m_layers.begin() + m_layer_insert_index, lay);
	m_layer_insert_index++;
}

void layer_stack::push_overlay(layer* overlay)
{
	// Layers get pushed into the very end of the vector.
	m_layers.emplace_back(overlay);
}

void layer_stack::pop_layer(layer* lay)
{
	// Look for layer among the pushed layers.
	auto it = std::find(m_layers.begin(), 
		m_layers.begin() + m_layer_insert_index, lay);
	if (it != m_layers.begin() + m_layer_insert_index)
	{
		lay->on_detach();
		m_layers.erase(it);
		m_layer_insert_index--;
	}
}

void layer_stack::pop_overlay(layer* overlay)
{
	// Look for overlay among the pushed overlays.
	auto it = std::find(m_layers.begin() + m_layer_insert_index,
		m_layers.end(), overlay);
	if (it != m_layers.end())
	{
		overlay->on_detach();
		m_layers.erase(it);
	}
}

std::vector<layer*>::iterator layer_stack::begin()
{
	return m_layers.begin();
}

std::vector<layer*>::iterator layer_stack::end()
{
	return m_layers.end();
}

std::vector<layer*>::reverse_iterator layer_stack::rbegin()
{
	return m_layers.rbegin();
}

std::vector<layer*>::reverse_iterator layer_stack::rend()
{
	return m_layers.rend();
}

std::vector<layer*>::const_iterator layer_stack::begin() const
{
	return m_layers.begin();
}

std::vector<layer*>::const_iterator layer_stack::end() const
{
	return m_layers.end();
}

std::vector<layer*>::const_reverse_iterator layer_stack::rbegin() const
{
	return m_layers.rbegin();
}

std::vector<layer*>::const_reverse_iterator layer_stack::rend() const
{
	return m_layers.rend();
}

}
