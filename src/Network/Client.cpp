#include "Sennet/pch.hpp"

#include "Sennet/Network/Client.hpp"

namespace Sennet
{

Client::Client()
{
}

Client::~Client()
{
	Disconnect();
}

bool Client::Connect(const std::string& host, const uint16_t& port)
{
	try
	{
		asio::ip::tcp::resolver resolver(m_Context);
		asio::ip::tcp::resolver::results_type endpoints =
			resolver.resolve(host, std::to_string(port));

		m_Connection = CreateScope<Connection>(
			Connection::Owner::Client, m_Context, m_MessagesIn);

		m_Connection->ConnectToServer(endpoints);

		m_ContextThread = std::thread([this]() { m_Context.run(); });
	}
	catch (std::exception& e)
	{
		SN_CORE_ERROR("[Client] Exception: {}", e.what());
		return false;
	}

	return true;
}

void Client::Disconnect()
{
	if (IsConnected())
	{
		m_Connection->Disconnect();
	}

	m_Context.stop();
	if (m_ContextThread.joinable())
	{
		m_ContextThread.join();
	}

	m_Connection.release();
}

bool Client::IsConnected()
{
	if (m_Connection)
	{
		return m_Connection->IsConnected();
	}
	else
	{
		return false;
	}
}

void Client::Send(const Ref<Message>& message)
{
	if (IsConnected())
	{
		m_Connection->Send(message);
	}
}

}
