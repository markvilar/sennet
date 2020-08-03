#include <sennet/messages/message_encoder.hpp>

#include <nop/serializer.h>
#include <nop/utility/die.h>
#include <nop/utility/stream_reader.h>
#include <nop/utility/stream_writer.h>

#include <sennet/messages/hello_world_message.hpp>

namespace 
{
	// Sends fatal errors to std::cerr.
	auto die() { return nop::Die(std::cerr); }
}  // anonymous namespace

namespace sennet
{

std::string* message_encoder::encode(const message& msg)
{
	// TODO: Optimize!
	// Get message type.
	auto msg_type = msg.get_message_type();

	// Serialize message. TODO: Cannot serialize through base pointer?
	using writer = nop::StreamWriter<std::stringstream>;
	nop::Serializer<writer> serializer;
	serializer.Write(msg);

	// Extract stringstream.
	std::stringstream msg_stream = serializer.writer().take();

	// Create parcel.
	message_header header;
	header.m_type= msg_type;
	header.m_message = msg_stream.str();

	// Serialize header.
	serializer.Write(header);
	std::stringstream hdr_stream = serializer.writer().take();
	auto hdr_string = new std::string(hdr_stream.str());

	SN_CORE_TRACE("Encoded: {0}", *hdr_string);
	return hdr_string;
}

message* message_encoder::decode(const std::string& raw_msg)
{
	// TODO: Optimize!
	
	// Set up reader.
	using Reader = nop::StreamReader<std::stringstream>;
	Reader header_reader(raw_msg);
	SN_CORE_TRACE("Reader stream: {0}", header_reader.stream().str());

	// Set up deserializer.
	nop::Deserializer<Reader*> header_deserializer(&header_reader);

	// Deserialize header.
	message_header header;
	header_deserializer.Read(&header); // Add die?

	SN_CORE_TRACE("Message header: {0}",
		static_cast<std::underlying_type<message_type>::type>(header.m_type)
		);

	// Get message type.
	//auto msg_ptr = type_to_class(header.m_type);
	hello_world_message* msg_ptr = new hello_world_message();

	// Deserialize message. TODO: Cannot deserialize through base pointer!
	header.m_message;
	Reader message_reader(header.m_message);
	nop::Deserializer<Reader*> message_deserializer(&message_reader);
	message_deserializer.Read(msg_ptr);

	SN_CORE_TRACE("Decoded: {0}", msg_ptr->get_name());
	return msg_ptr;
}

message* type_to_class(const message_type& type)
{
	switch (type)
	{
		case message_type::message:
			return new message();
		case message_type::hello_world_message:
			return new hello_world_message();
		default:
			return nullptr;
	}
}

}
