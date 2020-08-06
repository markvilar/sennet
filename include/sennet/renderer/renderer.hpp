#pragma once

namespace sennet
{

enum class renderer_api
{
	none = 0,
	opengl = 1
};

class renderer
{
public:
	inline static renderer_api get_api() { return s_renderer_api; }

private:
	static renderer_api s_renderer_api;
};

}
