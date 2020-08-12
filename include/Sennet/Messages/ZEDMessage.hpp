#pragma once

#include <Sennet/Messages/Message.hpp>

#include <Sennet/Primitives/Image.hpp>
#include <Sennet/Primitives/ZEDSettings.hpp>

namespace Sennet
{

enum class ZEDCommand
{
	None 		= 0,
	Initialize 	= 1,
	Shutdown 	= 2,
	StartRecord 	= 3,
	StopRecord 	= 4
};

class ZEDCommandRequest : public Request
{
public:
	ZEDCommandRequest() = default;
	ZEDCommandRequest(const std::string address, const unsigned int port,
		const ZEDCommand command)
		: Request(address, port), m_Command(command) {}
	virtual ~ZEDCommandRequest() = default;

	MESSAGE_CLASS_TYPE(ZEDCommandRequest);

	virtual std::string ToString() const override { return GetName(); }

	friend zpp::serializer::access;
	template <typename Archive, typename Self>
	static void serialize(Archive& archive, Self& self)
	{
		Request::serialize(archive, self);
		archive(self.m_Command);
	}

private:
	ZEDCommand m_Command;
};

class ZEDSettingsRequest : public Request
{
public:
	ZEDSettingsRequest() = default;
	ZEDSettingsRequest(const std::string address, 
		const unsigned int port,
		const ZED::InitParameters& initParameters,
		const ZED::RecordingParameters& recordingParameters,
		const ZED::RuntimeParameters& runtimeParameters);
	~ZEDSettingsRequest() = default;
	
	MESSAGE_CLASS_TYPE(ZEDSettingsRequest);

	virtual std::string ToString() const override { return GetName(); }

	friend zpp::serializer::access;
	template <typename Archive, typename Self>
	static void serialize(Archive& archive, Self& self)
	{
		Request::serialize(archive, self);
		archive(self.m_InitParameters);
		archive(self.m_RecordingParameters);
		archive(self.m_RuntimeParameters);
	}

private:
	ZED::InitParameters m_InitParameters;
	ZED::RecordingParameters m_RecordingParameters;
	ZED::RuntimeParameters m_RuntimeParameters;
};

class ZEDStateRequest : public Request
{
public:
	ZEDStateRequest() = default;
	ZEDStateRequest(const std::string address, const unsigned int port)
		: Request(address, port) {}
	~ZEDStateRequest() = default;

	MESSAGE_CLASS_TYPE(ZEDStateRequest);

	virtual std::string ToString() const override { return GetName(); }

	friend zpp::serializer::access;
	template <typename Archive, typename Self>
	static void serialize(Archive& archive, Self& self)
	{
		Request::serialize(archive, self);
	}

private:
};

enum class ZEDCommandFeedback
{
	None 			= 0,
	InitializeSuccess 	= 1,
	ShutdownSuccess 	= 2,
	StartRecordSuccess 	= 3,
	StopRecordSuccess 	= 4,
	InitializeFailure	= 5,
	ShutdownFailure		= 6,
	StartRecordFailure	= 7,
	StopRecordFailure	= 8
};

class ZEDCommandResponse: public Response
{
public:
	ZEDCommandResponse() = default;
	ZEDCommandResponse(const std::string address, const unsigned int port,
		const ZEDCommandFeedback feedback)
		: Response(address, port), m_CommandFeedback(feedback) {}
	~ZEDCommandResponse() = default;

	MESSAGE_CLASS_TYPE(ZEDCommandResponse);

	virtual std::string ToString() const override { return GetName(); }

	friend zpp::serializer::access;
	template <typename Archive, typename Self>
	static void serialize(Archive& archive, Self& self)
	{
		Response::serialize(archive, self);
		archive(self.m_CommandFeedback);
	}

private:
	ZEDCommandFeedback m_CommandFeedback;
};

enum class ZEDSettingsFeedback
{
	None 	= 0,
	Success = 1,
	Failure = 2
};

class ZEDSettingsResponse : public Response
{
public:
	ZEDSettingsResponse() = default;
	ZEDSettingsResponse(const std::string address, const unsigned int port)
		: Response(address, port) {}
	~ZEDSettingsResponse() = default;
	
	MESSAGE_CLASS_TYPE(ZEDSettingsResponse);

	virtual std::string ToString() const override { return GetName(); }

	friend zpp::serializer::access;
	template <typename Archive, typename Self>
	static void serialize(Archive& archive, Self& self)
	{
		Response::serialize(archive, self);
	}

private:
	ZED::RuntimeParameters m_RuntimeParameters;
};

class ZEDStateResponse: public Response
{
public:
	ZEDStateResponse() = default;
	ZEDStateResponse(const std::string address, 
		const unsigned int port,
		const ZED::InitParameters initParameters,
		const ZED::RecordingParameters recordingParameters,
		const ZED::RuntimeParameters runtimeParameters,
		const Image& image);
	~ZEDStateResponse() = default;

	MESSAGE_CLASS_TYPE(ZEDCommandResponse);

	virtual std::string ToString() const override { return GetName(); }

	friend zpp::serializer::access;
	template <typename Archive, typename Self>
	static void serialize(Archive& archive, Self& self)
	{
		Response::serialize(archive, self);
		archive(self.m_InitParameters);
		archive(self.m_RecordingParameters);
		archive(self.m_RuntimeParameters);
		archive(self.m_Image);
	}

private:
	ZED::InitParameters m_InitParameters;
	ZED::RecordingParameters m_RecordingParameters;
	ZED::RuntimeParameters m_RuntimeParameters;
	Image m_Image;
};

}
