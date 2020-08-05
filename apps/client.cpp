#include <functional>
#include <thread>

#include <sennet/sennet.hpp>

// Register messages.
namespace
{

zpp::serializer::register_types<
	zpp::serializer::make_type<sennet::hello_world_message,
	zpp::serializer::make_id("sennet::hello_world_message")>,
	zpp::serializer::make_type<sennet::image_message,
	zpp::serializer::make_id("sennet::image_message")>
> _;

}

void io_worker(sennet::connection_manager& manager)
{
	manager.run();
}

int main()
{
	sennet::log::init();
	sennet::connection_manager manager("6000", 1);
	SN_INFO("Client attempting to connect.");
	auto conn = manager.connect("localhost", "7000");
	manager.start();

	std::thread io_thread(io_worker, std::ref(manager));
	SN_INFO("Client: Started IO thread.");

	SN_INFO("Client: Sending messages.");
	sennet::hello_world_message hello_msg("hello world!");
	auto vec = std::vector<unsigned char>(1920*1080*3, 150);

	sennet::image_message img_msg(vec, 1920, 1080, 3, 
		sennet::zed::view::right);
		
	manager.push_message(conn, hello_msg);
	manager.push_message(conn, img_msg);

	if (io_thread.joinable())
	{
		io_thread.join();
	}

	SN_INFO("Client: Finished.");
	return 0;
}
