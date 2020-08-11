#include <Sennet/Messages/HelloMessage.hpp>

zpp::serializer::register_types<
	zpp::serializer::make_type<Sennet::HelloMessage,
	zpp::serializer::make_id("Sennet::HelloMessage")>
> _;


int main(int argc, char* argv[])
{
	Sennet::Log::Init();
	auto msg = Sennet::CreateRef<Sennet::HelloMessage>("halllllllo du");
	SN_INFO("Original message: {0}", msg->ToString());
	auto encoding = Sennet::MessageEncoder::Encode(msg);

	for (int i = 0; i < encoding->size(); i++)
	{
		std::cout << encoding->at(i);
	}
	std::cout << "\n";

	auto decodedMsg = Sennet::MessageEncoder::Decode(encoding);
	SN_INFO("Decoded message: {0}", decodedMsg->ToString());
	return 0;
}
