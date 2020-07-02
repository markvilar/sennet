#pragma once

#include <chrono>
#include <thread>
#include <string>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

#include <sennet/am/core.hpp>
#include <sennet/am/requests/request.hpp>
#include <sennet/serialization.hpp>

namespace am { 
namespace action {

class sleep : public request
{
	typedef boost::asio::ip::tcp asio_tcp;
	
public:
	// Default constructor.
	sleep()
		: request(),
		m_duration(0)
	{}

	// Copy constructor.
	sleep(const sleep& other)
		: request(other)
	{
		// TODO: Check that this is deep copy.
		m_duration = other.m_duration;
	}

	// Constructor.
	template <class Rep, class Period>
	sleep(
		const std::string& sender_addr,
		const unsigned short sender_port,
		std::chrono::duration<Rep, Period> duration
		)
		: request(sender_addr, sender_port),
		m_duration(std::chrono::duration_cast<decltype(m_duration)>
			(duration))
	{}

	// Constructor.
	template <class Rep, class Period>
	sleep(
		const asio_tcp::endpoint& sender_ep,
		std::chrono::duration<Rep, Period> duration
		)
		: request(sender_ep),
		m_duration(std::chrono::duration_cast<decltype(m_duration)>
			(duration))
	{}

	~sleep()
	{}

	void operator()(runtime& rt)
	{
		print();
		sleep_thread();
	}

	void operator()(zed_runtime& rt)
	{
		print();
		sleep_thread();
	}

	base_action* clone() const
	{
		return new sleep(*this);
	}

	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<request>(*this);
		ar & m_duration;
	}

	void print()
	{
		std::cout << "Sleeping for " << m_duration.count()
			<< " milliseconds.\n";
	}

	void sleep_thread()
	{
		std::this_thread::sleep_for(m_duration);
	}

private:
	std::chrono::milliseconds m_duration;

};

}
};

BOOST_CLASS_EXPORT_GUID(am::action::sleep, 
	"am::action::sleep");
