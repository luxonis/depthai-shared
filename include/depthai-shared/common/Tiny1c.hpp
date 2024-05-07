#pragma once

#include "depthai-shared/utility/Serialization.hpp"

namespace dai {
enum Tiny1cPropAutoShutterParams {
    /// Auto shutter update switch. 0:OFF, 1:ON
    SHUTTER_PROP_SWITCH = 0,

    /// Auto shutter minimun interval,to prevent updates too frequently.
    /// unit:1s, range:5-655
    SHUTTER_PROP_MIN_INTERVAL = 1,

    /// Auto shutter maximun interval,shutter updates automatically at this time.
    /// unit:1s, range:5-655
    SHUTTER_PROP_MAX_INTERVAL = 2,

    /// Vtemp's threshold to trigger OOC update in auto shutter.Do OOC update according to
    /// the temperature difference between latest update.
    /// unit:cnt(36cnt~=1c), range:0-65535
    SHUTTER_PROP_TEMP_THRESHOLD_OOC = 3,

    /// Vtemp's threshold to trigger B update in auto shutter.Do B update according to
    /// the temperature difference between latest update.
    /// unit:cnt(36cnt~=1c), range:0-65535
    SHUTTER_PROP_TEMP_THRESHOLD_B = 4,

    /// Shutter anti-fall protection switch. 0:OFF, 1:ON
    SHUTTER_PROP_PROTECT_SWITCH = 5,

    /// Manual shutter to auto shutter(or manual shutter)'s minimun interval,
    /// to prevent updates too frequently.
    /// unit:1s, range:0-655
    SHUTTER_PROP_ANY_INTERVAL = 6,

    /// Shutter anti-fall protection threshold in high gain mode.Range:0-65535.
    SHUTTER_PROTECT_THR_HIGH_GAIN = 7,

    /// Shutter anti-fall protection threshold in low gain mode.Range:0-65535.
    SHUTTER_PROTECT_THR_LOW_GAIN = 8,

    /// Calling shutter's fisrt delay time after preview start.
    /// unit:1s, range:0-655
    SHUTTER_PREVIEW_START_1ST_DELAY = 9,

    /// Calling shutter's delay time after fisrt delay.
    /// unit:1s, range:0-655
    SHUTTER_PREVIEW_START_2ND_DELAY = 10,

    /// Calling shutter's fisrt delay time after change gain.
    /// unit:1s, range:0-655
    SHUTTER_CHANGE_GAIN_1ST_DELAY = 11,

    /// Calling shutter's fisrt delay time after fisrt delay.
    /// unit:1s, range:0-655
    SHUTTER_CHANGE_GAIN_2ND_DELAY = 12
};
}
