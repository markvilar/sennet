#include "Sennet/pch.hpp"

#include "Sennet/Network/Endpoint.hpp"
#include "Sennet/Network/Socket.hpp"

#if defined(SN_NETWORK_ASIO)
	#include "Sennet/Platform/Asio/AsioSocket.hpp"
#endif

namespace Sennet
{

Scope<Socket> Socket::Create()
{
#if defined(SN_NETWORK_ASIO)
	return CreateScope<AsioSocket>();
#else
	SN_CORE_ASSERT(false, "Unsupported network API!");
	return nullptr;
#endif
}
}
