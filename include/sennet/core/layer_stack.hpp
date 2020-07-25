#pragma once

#include <sennet/snpch.hpp>

#include <sennet/core/base.hpp>
#include <sennet/core/layer.hpp>

namespace sennet
{

class layer_stack
{
public:
	layer_stack() = default;
	~layer_stack();

	void push_layer(layer* lay);
	void push_overlay(layer* overlay);
	void pop_layer(layer* lay);
	void pop_overlay(layer* overlay);

	std::vector<layer*>::iterator begin();
	std::vector<layer*>::iterator end();
	std::vector<layer*>::reverse_iterator rbegin();
	std::vector<layer*>::reverse_iterator rend();

	std::vector<layer*>::const_iterator begin() const;
	std::vector<layer*>::const_iterator end() const;
	std::vector<layer*>::const_reverse_iterator rbegin() const;
	std::vector<layer*>::const_reverse_iterator rend() const;

private:
	std::vector<layer*> m_layers;
	unsigned int m_layer_insert_index = 0;
};

}
