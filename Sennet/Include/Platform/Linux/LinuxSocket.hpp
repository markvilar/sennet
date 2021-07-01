#pragma once

#include "Sennet/Network/Socket.hpp"

namespace Sennet
{

class LinuxSocket : public Socket
{
public:
    LinuxSocket(const SocketSpecification& specs);
    virtual ~LinuxSocket() = default;

    // Generic methods.
    virtual void Open() override;
    virtual void Close() override;
    virtual size_t Send() override;
    virtual size_t Receive() override;

    // Server methods.
    virtual void Bind() override;
    virtual void Listen() override;
    virtual void Accept() override;

    // Client methods.
    virtual void Connect() override;
    virtual void Disconnect() override;

    // Status methods.
    virtual bool IsBound() override;
    virtual bool IsConnected() override;
    virtual bool IsOpen() override;

private:
    SocketSpecification m_Specifications; // TODO: Move to socket interface?
    int m_FileDescriptor = 0;
};

}
