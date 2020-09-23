#pragma once

#include <cstdint>


struct detection_t
{
    uint32_t label;
    float confidence;
    float x_min;
    float y_min;
    float x_max;
    float y_max;
    float depth_x;
    float depth_y;
    float depth_z;
};

struct detection_out_t
{
    int detection_count;
    detection_t detections[100];
};

struct nn_to_depth_bbox_map
{
    uint16_t offset_x;
    uint16_t offset_y;
    uint16_t max_width;
    uint16_t max_height;
};

