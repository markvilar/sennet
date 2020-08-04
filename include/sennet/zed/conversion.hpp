#pragma once

#include <memory>

#include <sl/Camera.hpp>

#include <sennet/sennet.hpp>

// Conversion function from sennet::zed types to sl types.
sl::VIEW to_stereolabs(const sennet::zed::view& sn_view);
sl::RESOLUTION to_stereolabs(const sennet::zed::resolution& sn_res);
sl::VIDEO_SETTINGS to_stereolabs(const sennet::zed::video_settings& sn_video);
sl::DEPTH_MODE to_stereolabs(const sennet::zed::depth_mode& sn_depth);
sl::UNIT to_stereolabs(const sennet::zed::unit& sn_unit);
sl::SVO_COMPRESSION_MODE to_stereolabs(
	const sennet::zed::svo_compression_mode& sn_compr);
sl::SENSING_MODE to_stereolabs(const sennet::zed::sensing_mode& sn_sensing);
sl::REFERENCE_FRAME to_stereolabs(const sennet::zed::reference_frame& sn_ref);
sl::COORDINATE_SYSTEM to_stereolabs(const sennet::zed::coordinate_system& sn_sys);

// Conversion function from sennet::zed classes to sl classes.
sennet::ref<sl::Mat> to_stereolabs(
	const sennet::ref<sennet::zed::image> sn_img);
sennet::ref<sl::InitParameters> to_stereolabs(
	const sennet::ref<sennet::zed::init_params> sn_ip);
sennet::ref<sl::RecordingParameters> to_stereolabs(
	const sennet::ref<sennet::zed::recording_params> sn_rp);
sennet::ref<sl::RuntimeParameters> to_stereolabs(
	const sennet::ref<sennet::zed::runtime_params> sn_rp);

// Conversion function from sl types to sennet::zed types.
sennet::zed::view to_sennet(const sl::VIEW& sl_view);
sennet::zed::resolution to_sennet(const sl::RESOLUTION& sl_res);
sennet::zed::video_settings to_sennet(const sl::VIDEO_SETTINGS& sl_video);
sennet::zed::depth_mode to_sennet(const sl::DEPTH_MODE& sl_depth);
sennet::zed::unit to_sennet(const sl::UNIT& sl_unit);
sennet::zed::svo_compression_mode to_sennet(
	const sl::SVO_COMPRESSION_MODE& sl_compr);
sennet::zed::sensing_mode to_sennet(const sl::SENSING_MODE& sl_sensing);
sennet::zed::reference_frame to_sennet(const sl::REFERENCE_FRAME& sl_ref);
sennet::zed::coordinate_system to_sennet(const sl::COORDINATE_SYSTEM& sl_sys);

// Conversion function from sl classes to sennet::zed classes.
sennet::ref<sennet::zed::image> to_sennet(
	const sennet::ref<sl::Mat> sl_img);
sennet::ref<sennet::zed::init_params> to_sennet(
	const sennet::ref<sl::InitParameters> sl_ip);
sennet::ref<sennet::zed::recording_params> to_sennet(
	const sennet::ref<sl::RecordingParameters> sl_rp);
sennet::ref<sennet::zed::runtime_params> to_sennet(
	const sennet::ref<sl::RuntimeParameters> sl_rp);
