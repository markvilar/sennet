#pragma once

#include <string>

#include <sl/Camera.hpp>

#include <sennet/am/core.hpp>
#include <sennet/am/responses/response.hpp>
#include <sennet/serialization.hpp>

namespace am { 
namespace action {

class zed_image : public response
{
	typedef boost::asio::ip::tcp boost_tcp;

public:
	// Default constructor.
	zed_image()
		: response()
	{
	}

	// Copy constructor.
	zed_image(const zed_image& other)
		: response(other)
	{
		// TODO: Problem here! clone() does not have const declaration.
		// Ensure deep copying of image.
		other.m_image.copyTo(m_image);
		m_timestamp = other.m_timestamp;
		m_view = other.m_view;
	}

	// Constructor.
	zed_image(
		const std::string sender_addr, 
		const unsigned short sender_port,
		const sl::Mat& m,
		const sl::Timestamp& t,
		const sl::VIEW& v
		)
		: response(sender_addr, sender_port)
	{
		m_image = m;
		m_timestamp = t;
		m_view = v;
	}

	// Constructor.
	zed_image(
		const boost_tcp::endpoint& sender_ep,
		const sl::Mat& m,
		const sl::Timestamp& t,
		const sl::VIEW& v
		)
		: response(sender_ep)
	{
		m_image = m;
		m_timestamp = t;
		m_view = v;
	}

	// Deconstructor.
	~zed_image()
	{
	}

	// Action for runtime.
	void operator()(runtime& rt)
	{
		std::cout << "Got ZED image!\n";
	}

	// Action for zed_runtime.
	void operator()(zed_runtime& rt)
	{
		std::cout << "Got ZED image!\n";
	}

	// Clones the object.
	base_action* clone() const
	{
		return new zed_image(*this);
	}

	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<response>(*this);
		ar & m_image;
		ar & m_timestamp;
		ar & m_view;
	}

private:
	sl::Mat m_image;
	sl::Timestamp m_timestamp;
	sl::VIEW m_view;
};

}
};

BOOST_CLASS_EXPORT_GUID(am::action::zed_image,
	"am::action::zed_image");
