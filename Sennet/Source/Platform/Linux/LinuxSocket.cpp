#include "Platform/Linux/LinuxSocket.hpp"

#include <sys/types.h>  // Data types for system calls.
#include <sys/socket.h> // Data structures needed for sockets.
#include <netinet/in.h> // Data structures for internet domain addresses.

namespace Sennet
{

LinuxSocket::LinuxSocket(const SocketSpecification& specs)
{
    int domain = AF_INET; 
    int socketType = SOCK_STREAM || SOCK_NONBLOCK;
    int opt = 1;

    // Create file descriptor.
    m_FileDescriptor = socket(domain, socketType, 0);
    SN_CORE_ASSERT(m_FileDescriptor >= 0, 
        "Error occured while creating socket.");

    setsockopt(m_FileDescriptor, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
        &opt, sizeof(opt));
}
    
void LinuxSocket::Open()
{
}

void LinuxSocket::Close()
{
}

size_t LinuxSocket::Send()
{
    // send(socket, buffer, bufferSize, flags);
    return 0;
}

size_t LinuxSocket::Receive()
{
    // recv(socket, buffer, bufferSize, flags);
    return 0;
}

// ----------------------------------------------------------------------------
// ---- Server methods --------------------------------------------------------
// ----------------------------------------------------------------------------

void LinuxSocket::Bind()
{
    int port = 8080;

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    auto bindStatus = bind(m_FileDescriptor, (struct sockaddr*)&address, 
        sizeof(address));
    SN_CORE_ASSERT(bindStatus == 0, "Error occured while binding socket.");
}

void LinuxSocket::Listen()
{
    int backlog = 3;
    auto listenStatus = listen(m_FileDescriptor, backlog);
    SN_CORE_ASSERT(listenStatus == 0, 
        "Error occured while listening on socket.");
}

void LinuxSocket::Accept()
{
    int port = 8080;

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    auto addressLength = sizeof(address);

    auto remote = accept(m_FileDescriptor, (struct sockaddr*)&address, 
        (socklen_t*)&addressLength);
    SN_CORE_ASSERT(remote >= 0, "Error occured while accepting connections.");
}

// ----------------------------------------------------------------------------
// ---- Client methods --------------------------------------------------------
// ----------------------------------------------------------------------------

void LinuxSocket::Connect()
{
    int port = 8080;

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);

    auto remote = connect(m_FileDescriptor, 
        (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    SN_CORE_ASSERT(remote >= 0, "Error occured while connecting to server.");
}

void LinuxSocket::Disconnect()
{
}

bool LinuxSocket::IsBound() 
{
    return false;
}

bool LinuxSocket::IsConnected()
{
    return false;
}

bool LinuxSocket::IsOpen()
{
    return false;
}

} // namespace Sennet
