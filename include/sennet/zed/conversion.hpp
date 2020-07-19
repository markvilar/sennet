#pragma once

#include <memory>

#include <sl/Camera.hpp>

#include <sennet/types/zed.hpp>

// Conversion function from sennet::zed types to sl types.
sl::VIEW to_stereolabs(const sennet::zed::view& x);
sl::RESOLUTION to_stereolabs(const sennet::zed::resolution& x);
sl::VIDEO_SETTINGS to_stereolabs(const sennet::zed::video_settings& x);
sl::DEPTH_MODE to_stereolabs(const sennet::zed::depth_mode& x);
sl::UNIT to_stereolabs(const sennet::zed::unit& x);
sl::SVO_COMPRESSION_MODE to_stereolabs(
	const sennet::zed::svo_compression_mode& x);
sl::SENSING_MODE to_stereolabs(const sennet::zed::sensing_mode& x);
sl::REFERENCE_FRAME to_stereolabs(const sennet::zed::reference_frame& x);
sl::COORDINATE_SYSTEM to_stereolabs(const sennet::zed::coordinate_system& x);

// Conversion function from sennet::zed classes to sl classes.
std::shared_ptr<sl::Mat> to_stereolabs(const sennet::zed::image& x);
sl::InitParameters to_stereolabs(const sennet::zed::init_params& x);
sl::RecordingParameters to_stereolabs(const sennet::zed::recording_params& x);
sl::RuntimeParameters to_stereolabs(const sennet::zed::runtime_params& x);

// Conversion function from sl types to sennet::zed types.
sennet::zed::view to_sennet(const sl::VIEW& x);
sennet::zed::resolution to_sennet(const sl::RESOLUTION& x);
sennet::zed::video_settings to_sennet(const sl::VIDEO_SETTINGS& x);
sennet::zed::depth_mode to_sennet(const sl::DEPTH_MODE& x);
sennet::zed::unit to_sennet(const sl::UNIT& x);
sennet::zed::svo_compression_mode to_sennet(const sl::SVO_COMPRESSION_MODE& x);
sennet::zed::sensing_mode to_sennet(const sl::SENSING_MODE& x);
sennet::zed::reference_frame to_sennet(const sl::REFERENCE_FRAME& x);

// Conversion function from sl classes to sennet::zed classes.
std::shared_ptr<sennet::zed::image> to_sennet(const sl::Mat& x);
sennet::zed::init_params to_sennet(const sl::InitParameters& x);
sennet::zed::recording_params to_sennet(const sl::RecordingParameters& x);
sennet::zed::runtime_params to_sennet(const sl::RuntimeParameters& x);
