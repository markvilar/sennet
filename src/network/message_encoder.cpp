#include <sennet/network/message_encoder.hpp>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/iostreams/stream.hpp>

#include <sennet/network/container_device.hpp>

namespace sennet
{

ref<std::vector<char>> message_encoder::encode(const message& msg)
{
	auto parcel = create_ref<std::vector<char>>();

	// Define I/O type.
	typedef container_device<std::vector<char>> io_device_type;

	// Create I/O stream in order to serialize action into parcel with an
	// archive.
	boost::iostreams::stream<io_device_type> io(*parcel);

	// Initialize action pointer to be input to archive.
	const message* msg_ptr = &msg;

	// Local scope in order to make sure archive goes out of scope before
	// proceeding.
	{
		boost::archive::binary_oarchive archive(io);
		archive & msg_ptr;
	}

	return parcel;
}

ref<message> message_encoder::decode(std::vector<char>& parcel)
{
	// Define I/O type.
	typedef container_device<std::vector<char>> io_device_type;

	// Create I/O stream in order to deserialize parcel into action with an
	// archive.
	boost::iostreams::stream<io_device_type> io(parcel);

	message* msg = nullptr;

	// Local scope in order to make sure archive goes out of scope before
	// proceeding.
	{
		boost::archive::binary_iarchive archive(io);
		archive & msg;
	}

	SN_CORE_ASSERT(msg, "In deserialize_parcel: Message pointer is null!");

	return create_ref<message>(*msg);
}

}
