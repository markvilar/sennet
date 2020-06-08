#pragma once

#include <string>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

#include <sl/Camera.hpp>

#include <zedutils/am/core.hpp>
#include <zedutils/am/requests/request.hpp>
#include <zedutils/am/responses/invalid_request.hpp>
#include <zedutils/am/responses/zed_image.hpp>
#include <zedutils/serialization.hpp>

namespace am { 
namespace action {

class zed_retrieve : public request
{
public:
	// Default constructor.
	zed_retrieve()
		: request()
	{
		// TODO: Implement.
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

	~zed_retrieve()
	{
		// TODO: Implement.
	}

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

		// TODO: Improve code for finding connection.
		// Find connection based on address and port.
		auto conn = rt.find_connection(addr, port);

		// Find connection based on address.
		if (!conn)
		{
			conn = rt.find_connection(addr);
		}

		// If connection is not found, we return.
		if (!conn)
		{
			return;
		}

		// Get local endpoint.
		auto local_ep = conn->get_local_endpoint();

		// If ZED is opened and recording.
		if (rt.is_zed_opened() && rt.is_zed_recording())
		{
			// TODO: Add assertions for ZED error code.
			sl::Mat img; 
			sl::Timestamp t_img;
			auto ec = rt.retrieve_zed_image(img, m_view);
			t_img = rt.get_zed_timestamp(m_time_ref);

			if (ec != sl::ERROR_CODE::SUCCESS)
				std::cout << sl::toVerbose(ec) << "\n";

			// Create image response and write over connection.
			zed_image response(local_ep.address().to_string(), 
				local_ep.port(), img, t_img, m_view);
			conn->async_write(response);
		}
		else
		{
			// Create invalid request response and write over
			// connection.
			invalid_request response(local_ep.address().to_string(),
				local_ep.port(), *this);
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
