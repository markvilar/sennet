#include <evpp/buffer.h>
#include <evpp/tcp_server.h>
#include <evpp/tcp_client.h>
#include <evpp/tcp_conn.h>

#include "Sennet/Sennet.hpp"

int main(int argc, char** argv)
{
    Sennet::Log::Init();
    SN_INFO("Hello world!");
}
