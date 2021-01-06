#pragma once

#include <cstdint>

//enum DetectionNetworkTypeEnum { dntype_yolo, dntype_mobilenet };

enum class DetectionNetworkType: std::int32_t  { YOLO, MOBILENET };
