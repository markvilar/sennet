#include <sstream>

#include "sennet/messages/message.hpp"
#include "sennet/messages/message_encoder.hpp"
#include "sennet/messages/hello_world_message.hpp"

int main(int argc, char* argv[])
{
	sennet::log::init();
	sennet::hello_world_message msg;
	SN_INFO("Got message");

	auto encoded_msg = sennet::message_encoder::encode(msg);
	auto decoded_msg = sennet::message_encoder::decode(*encoded_msg);

	if (decoded_msg)
		SN_INFO("Got decoded message");
	return 0;
}
