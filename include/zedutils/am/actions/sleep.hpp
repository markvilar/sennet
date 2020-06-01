#pragma once

#include <chrono>
#include <thread>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

#include <zedutils/am/actions/request.hpp>
#include <zedutils/am/core.hpp>
#include <zedutils/serialization.hpp>

namespace am { 
namespace action {

class sleep : public request
{
private:
	std::chrono::milliseconds m_duration;

public:
	sleep()
		: m_duration(0)
	{
	}

	template <class Rep, class Period>
	sleep(std::chrono::duration<Rep, Period> duration)
		: m_duration(
			std::chrono::duration_cast<decltype(m_duration)>
				(duration)
			)
	{
	}

	~sleep()
	{
	}

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
		return new sleep(m_duration);
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
};

}
};

BOOST_CLASS_EXPORT_GUID(am::action::sleep, 
	"am::action::sleep");
