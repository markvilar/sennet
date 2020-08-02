#include <sennet/messages/message_encoder.hpp>

#include <nop/serializer.h>
#include <nop/utility/die.h>
#include <nop/utility/stream_reader.h>
#include <nop/utility/stream_writer.h>

namespace 
{
	// Sends fatal errors to std::cerr.
	auto die() { return nop::Die(std::cerr); }
}  // anonymous namespace

namespace sennet
{

std::vector<char>* message_encoder::encode(const message& msg)
{
	// TODO: Optimize!
	// Get message type.
	auto msg_type = msg.get_message_type();

	// Serialize message.
	using writer = nop::StreamWriter<std::stringstream>;
	nop::Serializer<writer> serializer;
	serializer.Write(msg);

	// Extract stringstream.
	std::stringstream msg_stream = serializer.writer().take();
	std::string string_msg = msg_stream.str();
	std::vector<char> encoded_msg(string_msg.begin(), string_msg.end());

	// Create parcel.
	message_header header;
	header.m_type= msg_type;
	header.m_message = encoded_msg;

	// Serialize parcel.
	serializer.Write(header);
	std::string string_hdr = serializer.writer().stream().str();
	SN_CORE_TRACE("Encoded message: {0}", string_msg);
	SN_CORE_TRACE("Encoded header: {0}", string_hdr);

	return nullptr;
}

message* message_encoder::decode(std::vector<char>& raw_msg)
{
	// TODO: Implement.
	// Deserialize parcel.
	// Get message type.
	// Deserialize message.
	return nullptr;
}

}
