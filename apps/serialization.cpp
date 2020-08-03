#include <sstream>

#include <nop/serializer.h>
#include <nop/utility/die.h>
#include <nop/utility/stream_reader.h>
#include <nop/utility/stream_writer.h>

#include <sennet/messages/message.hpp>
#include <sennet/messages/message_encoder.hpp>
#include <sennet/messages/hello_world_message.hpp>

int main(int argc, char* argv[])
{
	/*
	This is the intended behaviour!!!
	*/
	sennet::log::init();
	sennet::message msg("hallo");
	sennet::hello_world_message hello("halllllllo du");
	SN_INFO("Got message: {0}", msg.to_string());
	SN_INFO("Got message: {0}", hello.to_string());

	// Write message.
	using writer = nop::StreamWriter<std::stringstream>;
	nop::Serializer<writer> serializer;
	serializer.Write(msg);
	std::stringstream msg_stream = serializer.writer().take();
	SN_INFO("Message: {0}", msg_stream.str());

	// Write hello_world_message.
	serializer.Write(hello);
	std::stringstream hello_stream = serializer.writer().take();
	SN_INFO("Hello message: {0}", hello_stream.str());

	// Read message.
	using Reader = nop::StreamReader<std::stringstream>;
	Reader msg_reader(msg_stream.str());
	nop::Deserializer<Reader*> msg_deserializer(&msg_reader);
	sennet::message* msg_ptr = new sennet::message;
	msg_deserializer.Read(msg_ptr);
	SN_INFO("Message: {0}", msg_ptr->to_string());

	
	// Read hello_world_message.
	Reader hello_reader(hello_stream.str());
	nop::Deserializer<Reader*> hello_deserializer(&hello_reader);
	sennet::hello_world_message* hello_ptr = new sennet::hello_world_message;
	hello_deserializer.Read(hello_ptr);
	SN_INFO("Message: {0}", hello_ptr->to_string());
	return 0;
}
