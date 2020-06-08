#include <chrono>	// std::chrono::seconds
#include <iostream>	// std::cout
#include <memory> 	// std::shared_ptr
#include <thread>	// std::this_thread

#include <boost/program_options.hpp>

#include <sl/Camera.hpp>

#include <zedutils/am/actions.hpp>
#include <zedutils/am/core.hpp>

void write_zed_open_action(std::shared_ptr<am::connection> conn)
{
	// Initialize ZED parameters.
	sl::InitParameters ips;
	ips.sdk_verbose = true;

	auto local_ep = conn->get_local_endpoint();

	// Initialize ZED open action.
	am::action::zed_open action(
		local_ep.address().to_string(),
		local_ep.port(),
		ips
		);

	// Send request to open ZED.
	conn->async_write(action,
		[](boost::system::error_code const& ec)
		{
			if (ec)
			{
				std::cout << "[ERROR] action: open\n"
					<< ec.message();
			}
			else
			{
				std::cout << "Open action written!\n";
			}
		});
}

void write_sleep_action(std::shared_ptr<am::connection> conn)
{
	auto local_ep = conn->get_local_endpoint();

	// Initialize ZED sleep action.
	am::action::sleep action(
		local_ep.address().to_string(),
		local_ep.port(),
		std::chrono::seconds(5)
		);

	conn->async_write(action,
		[](boost::system::error_code const& ec)
		{
			if (ec)
			{
				std::cout << "[ERROR] action: sleep\n"
					<< ec.message();
			}
			else
			{
				std::cout << "Sleep action written!\n";
			}
		});
}

void write_zed_retrieve_action(std::shared_ptr<am::connection> conn)
{
	auto local_ep = conn->get_local_endpoint();

	am::action::zed_retrieve action(
		local_ep.address().to_string(),
		local_ep.port(),
		sl::TIME_REFERENCE::IMAGE,
		sl::VIEW::LEFT
		);

	conn->async_write(action,
		[](boost::system::error_code const& ec)
		{
			if (ec)
			{
				std::cout << "[ERROR] action: retrieve\n"
					<< ec.message();
			}
			else
			{
				std::cout << "Retrieve action written!\n";
				std::cout << "Sleeping a bit...\n";
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}
		});
}

void write_zed_close_action(std::shared_ptr<am::connection> conn)
{
	// Initialize ZED close action.
	auto local_ep = conn->get_local_endpoint();
	am::action::zed_close action(
		local_ep.address().to_string(),
		local_ep.port()
		);

	conn->async_write(action,
		[](boost::system::error_code const& ec)
		{
			if (ec)
			{
				std::cout << "[ERROR] action: close\n"
					<< ec.message();
			}
			else
			{
				std::cout << "Close action written!\n";
			}
		});
}

void write_invalid_request_action(std::shared_ptr<am::connection> conn)
{
	am::action::invalid_request action;
	conn->async_write(action,
		[](boost::system::error_code const& ec)
		{
			if (ec)
			{
				std::cout << "[ERROR] action: invalid request\n"
					<< ec.message();
			}
		});
}

void write_list_connections_action(std::shared_ptr<am::connection> conn)
{
	auto local_ep = conn->get_local_endpoint();
	am::action::list_connections action(
		local_ep.address().to_string(),
		local_ep.port()
		);

	conn->async_write(action,
		[](boost::system::error_code const& ec)
		{
			if (ec)
			{
				std::cout << "[ERROR] action: invalid request\n"
					<< ec.message();
			}
		});
		
}

void zed_main(am::runtime& rt)
{
	namespace asio_ip = boost::asio::ip;
	std::cout << "Executing zed_main!\n";

	// We are searching for the server and therefore need the server side
	// IP address.
	std::string addr = "127.0.0.1";

	std::shared_ptr<am::connection> conn = rt.find_connection(addr);

	if (conn)
	{
		std::cout << "Found connection: " << addr << "\n";
		write_zed_open_action(conn);
		//write_sleep_action(conn);
		write_list_connections_action(conn);
		write_zed_retrieve_action(conn);
		write_zed_close_action(conn);
		//write_invalid_request_action(conn);
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

	std::shared_ptr<am::zed_runtime> rt;

	if (vm.count("remote-host") || vm.count("remote-port"))
	{
		rt.reset(new am::zed_runtime(port, root));

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
		rt.reset(new am::zed_runtime(port, root, zed_main));

		std::cout << "Running as client, will execute "
			<< "zed_main.\n";
	}

	rt->start();
	rt->run();

	return 0;
}
