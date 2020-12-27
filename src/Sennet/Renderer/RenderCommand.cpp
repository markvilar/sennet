#include "Sennet/Pch.hpp"
#include "Sennet/Renderer/RenderCommand.hpp"

namespace Sennet
{

Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}
