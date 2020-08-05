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

void handle_message(sennet::ref<sennet::message>& msg)
{
	SN_TRACE("Server: {0}", msg->to_string());
}

void io_worker(sennet::connection_manager& manager)
{
	manager.run();
}

int main()
{
	sennet::log::init();
	sennet::connection_manager manager("7000", 1);
	manager.set_message_callback(std::bind(handle_message, 
		std::placeholders::_1));
	manager.start();

	std::thread io_thread(io_worker, std::ref(manager));
	SN_TRACE("Server: Started IO thread.");

	if (io_thread.joinable())
	{
		io_thread.join();
	}

	SN_INFO("Server: Finished.");
	return 0;
}
