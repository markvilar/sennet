#pragma once

#include <string>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

#include <sl/Camera.hpp>

#include <zedutils/am/core.hpp>
#include <zedutils/am/requests/request.hpp>
#include <zedutils/am/responses/invalid_request.hpp>
#include <zedutils/serialization.hpp>

namespace am { 
namespace action {

class zed_grab: public request
{
	typedef boost::asio::ip::tcp asio_tcp;

public:
	// Default constructor.
	zed_grab()
		: request()
	{
		m_run_params = sl::RuntimeParameters();
		m_frames = 0;
	}

	// Copy constructor.
	zed_grab(const zed_grab& other)
		: request(other)
	{
		m_run_params = other.m_run_params;
		m_frames = other.m_frames;
	}

	// Constructor.
	zed_grab(
		const std::string sender_addr,
		const unsigned short sender_port,
		const sl::RuntimeParameters& run_params,
		const unsigned int frames
		)
		: request(sender_addr, sender_port)
	{
		m_run_params = run_params;
		m_frames = frames;
	}

	// Constructor.
	zed_grab(
		const asio_tcp::endpoint& sender_ep,
		const sl::RuntimeParameters& run_params,
		const unsigned int frames
		)
		: request(sender_ep)
	{
		m_run_params = run_params;
		m_frames = frames;
	}

	~zed_grab()
	{}

	// Action for runtime.
	void operator()(runtime& rt) override
	{
		std::cout << "This is a runtime. Invalid action.\n";
	}

	// Action for zed_runtime.
	void operator()(zed_runtime& rt) override
	{
		if (not rt.is_zed_opened())
		{
			std::cout << "Cannot perform ZED grab action.\n";
			std::cout << "Open status: " << rt.is_zed_opened() 
				<< "\n";
			std::cout << "Recording status: " 
				<< rt.is_zed_recording() << "\n";
			return;
		}

		std::cout << "Got ZED grab action!\n";
		unsigned int frames_recorded = 0;
		while (frames_recorded < m_frames)
		{
			if (rt.zed_grab(m_run_params) ==
				sl::ERROR_CODE::SUCCESS)
			{
				auto state = rt.zed_recording_status();
				if (state.status)
				{
					frames_recorded++;
				}
				std::cout << "Frame count: " << frames_recorded
					<< "\n";
			}
		}
	}

	// Clones the object.
	base_action* clone() const override
	{
		return new zed_grab(*this);
	}

	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<request>(*this);
		ar & m_run_params;
		ar & m_frames;
	}

private:
	sl::RuntimeParameters m_run_params;
	unsigned int m_frames;
};

}
};

BOOST_CLASS_EXPORT_GUID(am::action::zed_grab,
	"am::action::zed_grab");
