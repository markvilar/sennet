#include <iostream>
#include <memory>

#include <boost/program_options.hpp> 		// program_options

#include <zedutils/am/actions.hpp>
#include <zedutils/am/core.hpp>


void hello_world_main(am::runtime& rt)
{
	am::action::hello_world t;

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

int main(int argc, char** argv)
{
	namespace po = boost::program_options; 

	// Parse command line.
	po::variables_map vm;
	po::options_description cmdline(
		"Usage: test_hello_world --port <port> "
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

	std::shared_ptr<am::runtime> rt;

	if (vm.count("remote-host") || vm.count("remote-port"))
	{
		rt.reset(new am::runtime(port));

		std::cout << "Running as client, will not execute "
			<< "hello_world_main\n";

		std::string remote_host = "localhost";
		std::string remote_port = port;

		if (vm.count("remote-host"))
			remote_host = vm["remote-host"].as<std::string>();

		if (vm.count("remote-port"))
			remote_port = vm["remote-port"].as<std::string>();

		rt->connect(remote_host, remote_port);
	}
	else
	{
		rt.reset(new am::runtime(port, hello_world_main));

		std::cout << "Running as server, will execute "
			<< "hello_world_main\n";
	}

	rt->start();
	rt->run();
	
	return 0;
}
