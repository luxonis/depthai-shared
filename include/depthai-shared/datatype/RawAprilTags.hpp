#pragma once
#include <cstdint>
#include <vector>

#include "DatatypeEnum.hpp"
#include "RawAprilTagConfig.hpp"
#include "RawBuffer.hpp"
#include "depthai-shared/common/Point2f.hpp"
#include "depthai-shared/common/Rect.hpp"
#include "depthai-shared/utility/Serialization.hpp"

namespace dai {

/**
 * AprilTags structure.
 */
struct AprilTags {
    // The decoded ID of the tag
    int id;

    // How many error bits were corrected? Note: accepting large numbers of
    // corrected errors leads to greatly increased false positive rates.
    // NOTE: As of this implementation, the detector cannot detect tags with
    // a hamming distance greater than 2.
    int hamming;

    // A measure of the quality of the binary decoding process: the
    // average difference between the intensity of a data bit versus
    // the decision threshold. Higher numbers roughly indicate better
    // decodes. This is a reasonable measure of detection accuracy
    // only for very small tags-- not effective for larger tags (where
    // we could have sampled anywhere within a bit cell and still
    // gotten a good detection.)
    float decisionMargin;

    // The center of the detection in image pixel coordinates.
    Point2f center;

    // The corners of the tag in image pixel coordinates. These always
    // wrap counter-clock wise around the tag.
    dai::Rect points;
};
DEPTHAI_SERIALIZE_EXT(AprilTags, id, hamming, decisionMargin, center, points);

/// RawAprilTags structure
struct RawAprilTags : public RawBuffer {
    std::vector<AprilTags> aprilTags;

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) const override {
        metadata = utility::serialize(*this);
        datatype = DatatypeEnum::AprilTagData;
    };

    DEPTHAI_SERIALIZE(RawAprilTags, aprilTags);
};

}  // namespace dai
