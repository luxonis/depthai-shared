#pragma once

#include <vector>

#include "depthai-shared/common/CameraBoardSocket.hpp"
#include "depthai-shared/common/CameraImageOrientation.hpp"
#include "depthai-shared/datatype/RawCameraControl.hpp"
#include "depthai-shared/properties/Properties.hpp"
#include "depthai-shared/common/FrameEvent.hpp"

namespace dai {

/**
 * Specify properties for MonoCamera such as camera ID, ...
 */
struct MonoCameraProperties : PropertiesSerializable<Properties, MonoCameraProperties> {
    /**
     * Select the camera sensor resolution: 1280×720, 1280×800, 640×400, 640×480, 1920×1200
     */
    enum class SensorResolution : int32_t { THE_720_P, THE_800_P, THE_400_P, THE_480_P, THE_1200_P };

    /*
     * Initial controls applied to MonoCamera node
     */
    RawCameraControl initialControl;

    /**
     * Which socket will mono camera use
     */
    CameraBoardSocket boardSocket = CameraBoardSocket::AUTO;

    /**
     * Which camera name will mono camera use
     */
    std::string cameraName = "";

    /**
     * Camera sensor image orientation / pixel readout
     */
    CameraImageOrientation imageOrientation = CameraImageOrientation::AUTO;

    /**
     * Select the camera sensor resolution
     */
    SensorResolution resolution = SensorResolution::THE_720_P;
    /**
     * Camera sensor FPS
     */
    float fps = 30.0;
    /**
     * Frame pool size for the main output, ISP processed
     */
    int numFramesPool = 3;
    /**
     * Frame pool size for the `raw` output
     */
    int numFramesPoolRaw = 3;
    /**
     * List of events to receive, the rest will be ignored
     */
    std::vector<dai::FrameEvent> eventFilter;
};

DEPTHAI_SERIALIZE_EXT(MonoCameraProperties, initialControl, boardSocket, cameraName, imageOrientation, resolution, fps, numFramesPool, numFramesPoolRaw);

}  // namespace dai
