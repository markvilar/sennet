#pragma once

namespace Sennet
{

// TODO: UDP: AF_INET / SOCK_DGRAM
// TODO: TCP: AF_INET / SOCK_STREAM

// TODO: Windows: WSA initialization

enum class IPProtocol
{
    None = 0,
    TCP  = 1,
    UDP  = 2
};

struct SocketSpecification
{
    IPProtocol Protocol;
    bool KeepAlive;
    bool ReuseAddress;
    bool ReusePort;
    float Timeout;
};

class Socket
{
public:
    virtual ~Socket() = default;

    // Generic methods.
    virtual void Open() = 0;
    virtual void Close() = 0;
    virtual size_t Send() = 0;
    virtual size_t Receive() = 0;

    // Server methods.
    virtual void Bind() = 0;
    virtual void Listen() = 0;
    virtual void Accept() = 0;

    // Client methods.
    virtual void Connect() = 0;
    virtual void Disconnect() = 0;

    // Status methods.
    virtual bool IsBound() = 0;
    virtual bool IsConnected() = 0;
    virtual bool IsOpen() = 0;

    static Ref<Socket> Create(const SocketSpecification& specs);
};

}
