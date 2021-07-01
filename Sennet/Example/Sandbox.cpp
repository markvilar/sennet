#include "Sennet/Sennet.hpp"

int main(int argc, char** argv)
{
    Sennet::Log::Init();

    Sennet::SocketSpecification spec;

    auto socket = Sennet::Socket::Create(spec);
    socket->Bind();
    socket->Listen();
    socket->Accept();
}
