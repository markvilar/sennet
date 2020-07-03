#pragma once

#include <memory>

#include <sl/Camera.hpp>

#include <sennet/types/zed.hpp>

namespace sennet
{
	// Various functions to convert data Stereolabs data types into sennet
	// data types.

// TODO: Look into macros to implement these.
// Conversion function from sennet::zed types to sl types.
sl::VIEW to_stereolabs(const zed::view& x);
sl::RESOLUTION to_stereolabs(const zed::resolution& x);
sl::VIDEO_SETTINGS to_stereolabs(const zed::video_settings& x);
sl::DEPTH_MODE to_stereolabs(const zed::depth_mode& x);
sl::UNIT to_stereolabs(const zed::unit& x);
sl::SVO_COMPRESSION_MODE to_stereolabs(const zed::svo_compression_mode& x);
sl::SENSING_MODE to_stereolabs(const zed::sensing_mode& x);
sl::REFERENCE_FRAME to_stereolabs(const zed::reference_frame& x);

// Conversion function from sennet::zed classes to sl classes.
std::shared_ptr<sl::Mat> to_stereolabs(const zed::image& x);
sl::InitParameters to_stereolabs(const zed::init_params& x);
sl::RecordingParameters to_stereolabs(const zed::recording_params& x);
sl::RuntimeParameters to_stereolabs(const zed::runtime_params& x);

// Conversion function from sl types to sennet::zed types.
zed::view to_sennet(const sl::VIEW& x);
zed::resolution to_sennet(const sl::RESOLUTION& x);
zed::video_settings to_sennet(const sl::VIDEO_SETTINGS& x);
zed::depth_mode to_sennet(const sl::DEPTH_MODE& x);
zed::unit to_sennet(const sl::UNIT& x);
zed::svo_compression_mode to_sennet(const sl::SVO_COMPRESSION_MODE& x);
zed::sensing_mode to_sennet(const sl::SENSING_MODE& x);
zed::reference_frame to_sennet(const sl::REFERENCE_FRAME& x);

// Conversion function from sl classes to sennet::zed classes.
std::shared_ptr<zed::image> to_sennet(const sl::Mat& x);
zed::init_params to_sennet(const sl::InitParameters& x);
zed::recording_params to_sennet(const sl::RecordingParameters& x);
zed::runtime_params to_sennet(const sl::RuntimeParameters& x);

};
