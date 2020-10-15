#pragma once

namespace Sennet
{

class Socket
{
public:
	virtual ~Socket() = default;

	virtual void Read() const = 0;
	virtual void Write() const = 0;

	virtual void AsyncRead() const = 0;
	virtual void AsyncWrite() const = 0;

	virtual const Endpoint& GetLocalEndpoint() const = 0;
	virtual const Endpoint& GetRemoteEndpoint() const = 0;

	virtual void* GetNativeSocket() const = 0;

	static Scope<Socket> Create();

private:
	Endpoint m_LocalEndpoint;
	Endpoint m_RemoteEndpoint;
};

}
