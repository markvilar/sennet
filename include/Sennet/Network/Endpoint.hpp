#pragma once

namespace Sennet
{

enum class NetworkProtocol : uint8_t
{
	None = 0,
	TCP =  1,
	UDP =  2,
	HTTP = 3
};

class Endpoint
{
public:
	Endpoint(const std::string& address, const uint16_t& port, 
		const NetworkProtocol& protocol);
	~Endpoint() = default;

	const std::string& GetAddress() const { return m_Address; }
	const uint16_t& GetPort() const { return m_Port; }
	const NetworkProtocol& GetProtocol() const { return m_Protocol; }

	bool operator==(const Endpoint& other);
	bool operator!=(const Endpoint& other);

private:
	std::string m_Address;
	uint16_t m_Port;
	NetworkProtocol m_Protocol;
};

}

template<>
struct std::hash<Sennet::Endpoint>
{
	std::size_t operator()(const Sennet::Endpoint& ep) const
	{
		// Hash function for Sennet::Endpoints.
		return (std::hash<std::string>()(ep.GetAddress())
			^ (std::hash<uint16_t>()(ep.GetPort() << 1)) >> 1)
			^ (std::hash<Sennet::NetworkProtocol>()(
				ep.GetProtocol()) << 1);
	}
};
