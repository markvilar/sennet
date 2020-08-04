#include <sstream>

#include <sennet/messages/message.hpp>
#include <sennet/messages/message_encoder.hpp>
#include <sennet/messages/hello_world_message.hpp>

int main(int argc, char* argv[])
{
	sennet::log::init();
	auto msg = sennet::create_ref<sennet::hello_world_message>("halllllllo du");
	SN_INFO("Original message: {0}", msg->to_string());
	auto encoded_msg = sennet::message_encoder::encode(msg);

	for (int i = 0; i < encoded_msg->size(); i++)
	{
		std::cout << encoded_msg->at(i);
	}
	std::cout << "\n";

	auto decoded_msg = sennet::message_encoder::decode(encoded_msg);
	SN_INFO("Decoded message: {0}", decoded_msg->to_string());
	return 0;
}
