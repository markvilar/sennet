#pragma once

#include <string>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

#include <sl/Camera.hpp>

#include <sennet/am/core.hpp>
#include <sennet/am/requests/request.hpp>

namespace am { 
namespace action {

class zed_start_record : public request
{
	typedef boost::asio::ip::tcp asio_tcp;

public:
	// Default constructor.
	zed_start_record()
		: request()
	{
		m_rec_params = sl::RecordingParameters(
			"zed_recording.svo",
			sl::SVO_COMPRESSION_MODE::H264
			);
	}

	// Copy constructor.
	zed_start_record(const zed_start_record& other)
		: request(other)
	{
		// TODO: Ensure that this is deep copy.
		m_rec_params = other.m_rec_params;
	}

	// Constructor.
	zed_start_record(
		const std::string sender_addr,
		const unsigned short sender_port,
		const sl::RecordingParameters& rec_params
		)
		: request(sender_addr, sender_port)
	{
		m_rec_params = rec_params;
	}

	// Constructor.
	zed_start_record(
		const asio_tcp::endpoint& sender_ep,
		const sl::RecordingParameters& rec_params
		)
		: request(sender_ep)
	{
		m_rec_params = rec_params;
	}

	// Destructor.
	~zed_start_record()
	{}

	// Gets the recording parameters.
	sl::RecordingParameters get_rec_params() const { return m_rec_params; }

	// Sets the recording parameters.
	inline void set_rec_params(const sl::RecordingParameters& rec_params)
	{
		m_rec_params = rec_params;
	}

	void operator()(runtime& rt)
	{
		// TODO: Add logging.
		auto [addr, port] = get_sender();
		auto conn = rt.find_connection(addr, port);
		if (conn)
		{
			invalid_request response(conn->get_local_endpoint(), *this);
			conn->async_write(response);
		}
	}

	void operator()(zed_runtime& rt)
	{
		auto [addr, port] = get_sender();
		auto conn = rt.find_connection(addr, port);
		response* reply = nullptr;

		if (conn and rt.is_zed_opened() and not rt.is_zed_recording())
		{
			// Camera ready. Start recording.
			auto ec = rt.enable_zed_recording(m_rec_params);
			if (ec != sl::ERROR_CODE::SUCCESS)
			{
				// TODO: Add error response.
				conn->async_write(invalid_request(
					conn->get_local_endpoint(),
					*this
					));
			}
			else
			{
				std::cout << "Enabled recording.\n";
			}
		}
		else if (conn)
		{
			conn->async_write(invalid_request(
				conn->get_local_endpoint(),
				*this
				));
		}
	}

	base_action* clone() const
	{
		return new zed_start_record(*this);
	}

	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<request>(*this);
		ar & m_rec_params;
	}

private:
	sl::RecordingParameters m_rec_params;
};

}
};

BOOST_CLASS_EXPORT_GUID(am::action::zed_start_record,
	"am::action::zed_start_record");
