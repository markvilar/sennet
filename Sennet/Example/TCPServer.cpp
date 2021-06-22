#include <string>

#include <evpp/buffer.h>
#include <evpp/timestamp.h>
#include <evpp/tcp_server.h>
#include <evpp/tcp_client.h>
#include <evpp/tcp_conn.h>

#include "Sennet/Sennet.hpp"

void MessageCallback(const evpp::TCPConnPtr& conn, evpp::Buffer* msg) 
{
    conn->Send(msg);
}


void ConnectionCallback(const evpp::TCPConnPtr& conn) 
{
    if (conn->IsConnected()) 
    {
        SN_INFO("A new connection from {0}", conn->remote_addr());
    } 
    else 
    {
        SN_INFO("Lost the connection from {0}", conn->remote_addr());
    }
}

int main(int argc, char* argv[])
{
    Sennet::Log::Init();

    // Sennet::IPAddress address("128.0.0.1", 1080);
    // Sennet::Server server(loop, address, name, threads);

    std::string addr = "0.0.0.0:9099";
    int thread_num = 4;

    evpp::EventLoop loop;
    evpp::TCPServer server(&loop, addr, "TCPEchoServer", thread_num);
    server.SetMessageCallback(MessageCallback);

    server.SetConnectionCallback(ConnectionCallback);

    server.Init();
    server.Start();
    loop.Run();
    return 0;
}
