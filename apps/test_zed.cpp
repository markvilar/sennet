#include <iostream>
#include <memory>

#include <boost/program_options.hpp>

#include <sl/Camera.hpp>

#include <zedutils/active_messaging/zed.hpp>

void zed_main(zed::am::runtime& rt)
{
	std::cout << "Executing zed_main!\n";
	zed::am::open_camera_request t;

	auto conns = rt.get_connections();

	std::shared_ptr<boost::uint64_t> count(
		new boost::uint64_t(conns.size()));

	for (auto node : conns)
		node.second->async_write(t,
			[count, &rt](boost::system::error_code const& ec)
			{
				if (--(*count) == 0)
					rt.stop();
			});
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

		std::cout << "Running as client, will not execute "
			<< "zed_main.\n";
	}
	else
	{
		rt.reset(new zed::am::zed_runtime(port, root, zed_main));

		std::cout << "Running as server, will execute "
			<< "zed_main.\n";
	}

	rt->start();
	rt->run();

	return 0;
}
