#include "Sennet/pch.hpp"
#include "Sennet/Network/Endpoint.hpp"

namespace Sennet
{

Endpoint::Endpoint(const std::string& address, const uint16_t& port, 
	const NetworkProtocol& protocol)
	: m_Address(address), m_Port(port), m_Protocol(protocol)
{
}

bool Endpoint::operator==(const Endpoint& other)
{
	return m_Address == other.m_Address 
		&& m_Port == other.m_Port 
		&& m_Protocol == other.m_Protocol;
}

bool Endpoint::operator!=(const Endpoint& other)
{
	return !(*this == other);
}

}
