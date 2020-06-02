#include <iostream>
#include <tuple>

#include <boost/asio.hpp>

#include <glad/glad.h>

#include <zedutils/am/actions.hpp>
#include <zedutils/am/core.hpp>

void print_endpoint(
	const std::string header,
	const std::string addr, 
	const unsigned short port)
{
	std::cout << header << "\n";
	std::cout << " - address: " << addr << "\n";
	std::cout << " - port:    " << port << "\n";
}

void test_constructor_1()
{
	am::action::zed_close close_action;
	auto[addr, port] = close_action.get_sender();
	print_endpoint("sender", addr, port);
}

void test_constructor_2()
{
	am::action::zed_close close_action("127.0.0.1", 6000);
	auto[addr, port] = close_action.get_sender();
	print_endpoint("sender", addr, port);
}

void test_constructor_3()
{
	am::action::zed_close close_action(
		"127.0.0.1", 
		6000,
		"196.0.1.5",
		5000);
	auto[s_addr, s_port] = close_action.get_sender();
	auto[r_addr, r_port] = close_action.get_responder();
	print_endpoint("sender", s_addr, s_port);
	print_endpoint("responder", r_addr, r_port);
	std::cout << "has responder: " << close_action.has_responder() << "\n";
}

void test_endpoint_comparison()
{
	am::action::zed_close close_action("127.0.0.1", 6000,
		"196.0.1.5", 5000);
		
	// boost::asio::ip::address, unsigned short port_num
	boost::asio::ip::tcp::endpoint ep(
		boost::asio::ip::address::from_string("196.0.1.5"),
		5000);

	std::cout << close_action.is_responder(ep) << "\n";
}

int main()
{
	test_constructor_1();
	test_constructor_2();
	test_constructor_3();
	test_endpoint_comparison();
	return 0;
}
