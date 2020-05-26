#include <chrono>	// std::chrono::seconds
#include <iostream>	// std::cout
#include <memory> 	// std::shared_ptr
#include <thread>	// std::this_thread

#include <boost/program_options.hpp>

#include <sl/Camera.hpp>

#include <zedutils/active_messaging/action.hpp>
#include <zedutils/active_messaging/runtime.hpp>

void zed_main(zed::am::runtime& rt)
{
	std::cout << "Executing zed_main!\n";

	// ZED initialization parameters.
	sl::InitParameters ips;
	ips.sdk_verbose = true;

	// Actions.
	zed::am::zed_open_request open_action(ips);
	zed::am::zed_close_request close_action;

	auto conns = rt.get_connections();

	std::shared_ptr<boost::uint64_t> count(
		new boost::uint64_t(conns.size()));

	boost::asio::ip::address address;
	unsigned short port;
	for (auto node : conns)
	{
		// Node: std::map< endpoint, shared_ptr<connection> >
		address = node.first.address();
		port = node.first.port();

		std::cout << "\nNode " << --(*count) << "\n";
		std::cout << "- Address: " << address << "\n";
		std::cout << "- Port: " << port << "\n";

		// Send request to open ZED.
		node.second->async_write(open_action,
			[&address, &port](
				boost::system::error_code const& ec
				)
			{
				if (ec)
				{
					std::cout << "Error when writing ZED "
						<< "open action to address "
						<< address << " on port " 
						<< port << ".\n"
						<< " - " << ec.value() << "\n";
				}
			});
	}

	for (auto node: conns)
	{
		address = node.first.address();
		port = node.first.port();
		
		// Send request to close ZED.
		node.second->async_write(close_action,
			[&address, &port](boost::system::error_code const& ec)
			{
				if (ec)
				{
					std::cout << "Error when writing ZED "
						<< "close action to address "
						<< address << " on port " 
						<< port << ".\n"
						<< " - " << ec.value() << "\n";
				}
			});
	}
}

int main(int argc, char* argv[])
{
	namespace po = boost::program_options;

	// TODO: Integrate into command line options.
	// Root directory for data storage.
	std::string root = "/home/martin/dev/zedutils/data";
	
	// Parse command line.
	po::variables_map vm;
	po::options_description cmdline(
		"Usage: test_zed --port <port> "
		"[--remote-host <hostname> --remote-port <port>]");

	cmdline.add_options()
		("help, h",
		"print out program usage (this message)")
		("port",
		po::value<std::string>()->default_value("9000"),
		"TCP port to listen on")
		("remote-host",
		po::value<std::string>(),
		"hostname or IP to connect to")
		("remote-port",
		po::value<std::string>(),
		"TCP port to connect to");

	po::store(po::command_line_parser(argc, argv).options(cmdline).run(),
		vm);

	po::notify(vm);

	// Print help screen.
	if (vm.count("help"))
	{
		std::cout << cmdline;
		return 1;
	}

	std::string port = vm["port"].as<std::string>();

	std::shared_ptr<zed::am::zed_runtime> rt;

	if (vm.count("remote-host") || vm.count("remote-port"))
	{
		rt.reset(new zed::am::zed_runtime(port, root));

		std::string remote_host = "localhost";
		std::string remote_port = port;

		if (vm.count("remote-host"))
			remote_host = vm["remote-host"].as<std::string>();

		if (vm.count("remote-port"))
			remote_port = vm["remote-port"].as<std::string>();

		// Since we connect here, this is a client.
		rt->connect(remote_host, remote_port);

		std::cout << "Running as server, will not execute "
			<< "zed_main.\n";
	}
	else
	{
		rt.reset(new zed::am::zed_runtime(port, root, zed_main));

		std::cout << "Running as client, will execute "
			<< "zed_main.\n";
	}

	rt->start();
	rt->run();

	return 0;
}
