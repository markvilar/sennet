#include <sennet/pch.hpp>
#include <sennet/renderer/vertex_array.hpp>

#include <sennet/renderer/renderer.hpp>
#include <sennet/platform/opengl/opengl_vertex_array.hpp>

namespace sennet
{

vertex_array* vertex_array::create()
{
	switch (renderer::get_api())
	{
		case renderer_api::none: 
			SN_CORE_ASSERT(false, "renderer_api::none is currently \
				not supported!");
		case renderer_api::opengl:
			return new opengl_vertex_array();
	}
	
	SN_CORE_ASSERT(false, "Unknown renderer API.");
	return nullptr;
}

}
