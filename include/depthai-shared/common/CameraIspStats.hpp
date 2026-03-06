#pragma once

#include <cstdint>

#include "depthai-shared/common/CameraBoardSocket.hpp"
#include "depthai-shared/utility/Serialization.hpp"

namespace dai {

/**
 * Camera ISP control statistics
 */
struct CameraIspStats {
    CameraBoardSocket socket = CameraBoardSocket::AUTO;
    int32_t cameraId = -1;
    int32_t chanNo = -1;
    uint32_t seqNo = 0;
    uint32_t srcConfigured = 0;
    uint32_t srcStarted = 0;
    uint32_t srcReadStoped = 0;
    uint32_t srcReadStart = 0;
    uint32_t srcReadEnd = 0;
    uint32_t ispStarts = 0;
    uint32_t ispEnds = 0;
    uint32_t ispStatsReady = 0;
    uint32_t errMipiNoOutBuf = 0;
    uint32_t errMipiCfgSkipped = 0;
    uint32_t errMipiCfgMiss = 0;
    uint32_t errMipiWrongState = 0;
    uint32_t errEventError = 0;
};

DEPTHAI_SERIALIZE_EXT(CameraIspStats,
                      socket,
                      cameraId,
                      chanNo,
                      seqNo,
                      srcConfigured,
                      srcStarted,
                      srcReadStoped,
                      srcReadStart,
                      srcReadEnd,
                      ispStarts,
                      ispEnds,
                      ispStatsReady,
                      errMipiNoOutBuf,
                      errMipiCfgSkipped,
                      errMipiCfgMiss,
                      errMipiWrongState,
                      errEventError);

}  // namespace dai
