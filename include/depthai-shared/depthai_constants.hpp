#pragma once
// TODO: this file should be removed, and all configurations passed to device via USB
// (e.g over config_h2d)


#include <climits>
#include <unordered_map>
#include <vector>

#include "stream/stream_info.hpp"

#include "metadata/frame_metadata.hpp"
#include "metadata/capture_metadata.hpp"


#define MONO_RES_AUTO  (-2)
#define MONO_MAX_W  1280
#define MONO_MAX_H   800


constexpr int MONO_MAX_SIZE(int n_planes, int elem_size) {
   return (MONO_MAX_W * MONO_MAX_H * (n_planes) * (elem_size) + sizeof(FrameMetadata));
}

// TODO: remove next constant
std::unordered_map<std::string, StreamInfo> g_streams_pc_to_myriad =
{
    {"config_h2d",     StreamInfo("config_h2d",     1024*1024)},
    {"host_capture",     StreamInfo("host_capture",     sizeof(CaptureMetadata))}
};


std::unordered_map<std::string, StreamInfo> c_streams_myriad_to_pc =
{
    {"left",        StreamInfo("left",      MONO_MAX_SIZE(1,1), { MONO_RES_AUTO, 0} )},
    {"right",       StreamInfo("right",     MONO_MAX_SIZE(1,1), { MONO_RES_AUTO, 0} )},
    {"disparity",   StreamInfo("disparity", MONO_MAX_SIZE(1,1), { MONO_RES_AUTO, 0} )},
    {"rectified_left",  StreamInfo("rectified_left",  MONO_MAX_SIZE(1,1), { MONO_RES_AUTO, 0} )},
    {"rectified_right", StreamInfo("rectified_right", MONO_MAX_SIZE(1,1), { MONO_RES_AUTO, 0} )},

    // {"depth",       StreamInfo("depth",     921600, { 720, 1280}    )},
    {"depth",  StreamInfo("depth",      MONO_MAX_SIZE(1,2), { MONO_RES_AUTO, 0}, 2 )},
    {"disparity_color", StreamInfo("disparity_color", MONO_MAX_SIZE(3,1), { MONO_RES_AUTO, 0, 3} )},

    {"metaout",     StreamInfo("metaout",    4*1024*1024)}, // 4 mb max metaout size
    {"previewout",  StreamInfo("previewout", 1920256)},

    {"meta_d2h",    StreamInfo("meta_d2h",   1024*1024)},
    {"jpegout",    StreamInfo("jpegout",   10*1024*1024)},
    {"video",    StreamInfo("video",   10*1024*1024)},
    {"object_tracker",    StreamInfo("object_tracker",   2000)},
    {"color",    StreamInfo("color",   20*1024*1024)},
};
