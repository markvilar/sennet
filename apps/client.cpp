#include <functional>
#include <thread>

#include <sennet/sennet.hpp>

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

	sennet::message msg("gunnar");
	for (int i = 0; i < 1; i++)
	{
		if (conn)
		{
			manager.push_message(conn, msg);
		}
	}

	SN_INFO("Client: {0}", msg.to_string());

	if (io_thread.joinable())
	{
		io_thread.join();
	}

	SN_INFO("Client: Finished.");
	return 0;
}
