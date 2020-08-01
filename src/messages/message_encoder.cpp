#include <sennet/messages/message_encoder.hpp>

namespace sennet
{

std::vector<char>* message_encoder::encode(const message& msg)
{
	// TODO: Implement.
	// Get message type.
	// Serialize message.
	// Create parcel.
	// Serialize parcel.
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
