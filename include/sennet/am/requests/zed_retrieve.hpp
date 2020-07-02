#pragma once

#include <string>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

#include <sl/Camera.hpp>

#include <sennet/am/core.hpp>
#include <sennet/am/requests/request.hpp>
#include <sennet/am/responses/invalid_request.hpp>
#include <sennet/am/responses/zed_image.hpp>
#include <sennet/serialization.hpp>

namespace am { 
namespace action {

class zed_retrieve : public request
{
	typedef boost::asio::ip::tcp asio_tcp;

public:
	// Default constructor.
	zed_retrieve()
		: request()
	{
		m_time_ref = sl::TIME_REFERENCE::IMAGE;
		m_view = sl::VIEW::LEFT;
	}

	// Copy constructor.
	zed_retrieve(const zed_retrieve& other)
		: request(other)
	{
		m_time_ref = other.m_time_ref;
		m_view = other.m_view;
	}

	// Constructor.
	zed_retrieve(
		const std::string sender_addr,
		const unsigned short sender_port,
		const sl::TIME_REFERENCE& time_ref,
		const sl::VIEW view
		)
		: request(sender_addr, sender_port)
	{
		m_time_ref = time_ref;
		m_view = view;
	}

	// Constructor.
	zed_retrieve(
		const asio_tcp::endpoint& sender_ep,
		const sl::TIME_REFERENCE& time_ref,
		const sl::VIEW view
		)
		: request(sender_ep)
	{
		m_time_ref = time_ref;
		m_view = view;
	}

	~zed_retrieve()
	{}

	// Gets the stereo view.
	sl::VIEW get_view() const { return m_view; }

	// Sets the stereo view.
	inline void set_view(sl::VIEW& view) { m_view = view; }

	// Action for runtime.
	void operator()(runtime& rt) override
	{
		std::cout << "This is a runtime. Cannot retrieve ZED image...\n";
	}

	// Action for zed_runtime.
	void operator()(zed_runtime& rt) override
	{
		std::cout << "Got ZED retrieve action!\n";

		// Get IP address and port to send image to.
		auto [addr, port] = get_sender();
		auto conn = rt.find_connection(addr, port);
		
		// If we found connection, ZED is opened and recording.
		if (conn and rt.is_zed_opened() and rt.is_zed_recording())
		{
			// TODO: Add assertions for ZED error code.
			sl::Mat img; 
			sl::Timestamp t_img;
			auto ec = rt.retrieve_zed_image(img, m_view);
			t_img = rt.get_zed_timestamp(m_time_ref);

			if (ec != sl::ERROR_CODE::SUCCESS)
				std::cout << sl::toVerbose(ec) << "\n";

			// Create image response and write over connection.
			zed_image response(
				conn->get_local_endpoint(),
				img, 
				t_img, 
				m_view
				);
			conn->async_write(response);
		}
		else if (conn)
		{
			// Create invalid request response and write over
			// connection.
			invalid_request response(
				conn->get_local_endpoint(),
				*this
				);
			conn->async_write(response);
		}
	}

	// Clones the object.
	base_action* clone() const override
	{
		return new zed_retrieve(*this);
	}

	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<request>(*this);
		ar & m_time_ref;
		ar & m_view;
	}

private:
	sl::TIME_REFERENCE m_time_ref;
	sl::VIEW m_view;
};

}
};

BOOST_CLASS_EXPORT_GUID(am::action::zed_retrieve,
	"am::action::zed_retrieve");
