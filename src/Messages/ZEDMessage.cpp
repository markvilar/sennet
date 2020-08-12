#include <Sennet/pch.hpp>
#include <Sennet/Messages/ZEDMessage.hpp>

namespace Sennet
{

ZEDSettingsRequest::ZEDSettingsRequest(const std::string address, 
	const unsigned int port,
	const ZED::InitParameters& initParameters,
	const ZED::RecordingParameters& recordingParameters,
	const ZED::RuntimeParameters& runtimeParameters)
	: Request(address, port), m_InitParameters(initParameters),
	m_RecordingParameters(recordingParameters),
	m_RuntimeParameters(runtimeParameters)
{
}

ZEDStateResponse::ZEDStateResponse(const std::string address, 
	const unsigned int port,
	const ZED::InitParameters initParameters,
	const ZED::RecordingParameters recordingParameters,
	const ZED::RuntimeParameters runtimeParameters,
	const Image& image)
	: Response(address, port), m_InitParameters(initParameters),
	m_RecordingParameters(recordingParameters), 
	m_RuntimeParameters(runtimeParameters)
{
}

}
