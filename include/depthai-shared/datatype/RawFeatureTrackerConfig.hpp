#pragma once
#include <cstdint>
#include <nlohmann/json.hpp>
#include <vector>

#include "DatatypeEnum.hpp"
#include "RawBuffer.hpp"

namespace dai {

/// FeatureTracker configuration data structure
struct FeatureTrackerConfigData {
    struct CornerDetector {
        enum class AlgorithmType : std::int32_t {
            /**
             * Harris corner detector.
             */
            HARRIS,
            /**
             * Shi-Thomasi corner detector.
             */
            SHI_THOMASI
        };
        AlgorithmType algorithmType = AlgorithmType::HARRIS;

        /**
         * Ensures distributed feature detection across the image.
         * Image is divided into numImageCells horizontal and vertical cells,
         * each cell has a target feature count = targetNumFeatures / numImageCells.
         * Each cell has it's own feature threshold.
         * A value of 4 means that the image is divided into 4x4 cells of equal width/height.
         * Maximum 4, minimum 1.
         */
        std::int32_t numImageCells = 4;

        /**
         * Target number of features to detect.
         * Maximum number of features is determined at runtime based on algorithm type.
         */
        std::int32_t targetNumFeatures = 320;

        /**
         * Hard limit for the maximum number of features that can be detected.
         * 0 means auto, will be set to the maximum value based on memory constraints.
         */
        std::int32_t maxNumFeatures = 0;

        /**
         * Threshold settings for corner detector.
         * These are advanced settings, suitable for debugging/special cases.
         */
        struct Thresholds {
            static constexpr const float AUTO = 0;

            /**
             * Minimum strength of a feature which will be detected.
             * 0 means automatic threshold update. Recommended so the tracker can adapt to different scenes/textures.
             * Each chell has its own threshold.
             * Empirical value.
             */
            float initialValue = AUTO;

            /**
             * Minimum limit for threshold.
             * Applicable when automatic threshold update is enabled.
             * 0 means auto, 6000000 for HARRIS, 1200 for SHI_THOMASI
             * Empirical value.
             */
            float min = AUTO;

            /**
             * Maximum limit for threshold.
             * Applicable when automatic threshold update is enabled.
             * 0 means auto.
             * Empirical value.
             */
            float max = AUTO;

            /**
             * When detected number of features exceeds the maximum in a cell threshold is lowered
             * by multiplying its value with this factor.
             */
            float decreaseFactor = 0.9;

            /**
             * When detected number of features doesn't exceed the maximum in a cell threshold is increased
             * by multiplying its value with this factor.
             */
            float increaseFactor = 1.1;
        };

        Thresholds thresholds;
    };

    /**
     * Used for feature reidentification between current and previous features.
     */
    struct MotionEstimator {
        static constexpr const std::int32_t AUTO = 0;

        bool enable = true;

        enum class AlgorithmType : std::int32_t {
            /**
             * Using the pyramidal Lucas-Kanade optical flow method.
             */
            LUCAS_KANADE_OPTICAL_FLOW
        };
        AlgorithmType algorithmType = AlgorithmType::LUCAS_KANADE_OPTICAL_FLOW;

        /**
         * Number of pyramid levels, only for optical flow.
         * AUTO means it's decided based on input resolution: 3 if image width <= 640, else 4.
         */
        std::int32_t pyramidLevels = AUTO;

        /**
         * Image patch width used to track features.
         * Must be an odd number, maximum 23.
         * N means the algorithm will be able to track motion at most (N-1)/2 pixels in a direction per pyramid level.
         * Increasing this number increases runtime
         */
        std::int32_t searchWindowWidth = 5;
        /**
         * Image patch height used to track features.
         * Must be an odd number, maximum 23.
         * N means the algorithm will be able to track motion at most (N-1)/2 pixels in a direction per pyramid level.
         * Increasing this number increases runtime
         */
        std::int32_t searchWindowHeight = 5;

        /**
         * Feature tracking termination criteria.
         * Optical flow will refine the feature position on each pyramid level until
         * the displacement between two refinements is smaller than this value.
         * Decreasing this number increases runtime.
         */
        float epsilon = 0.01;

        /**
         * Feature tracking termination criteria. Optical flow will refine the feature position maximum this many times
         * on each pyramid level. If the Epsilon criteria described in the previous chapter is not met after this number
         * of iterations, the algorithm will continue with the current calculated value.
         * Increasing this number increases runtime.
         */
        std::int32_t maxIterations = 9;
    };

    /**
     * Used for feature filtering.
     */
    struct FeatureMaintainer {
        bool enable = true;

        /**
         * Used to filter out detectoed feature points that are too close.
         * Unit of measurement is squared euclidian distance in pixels.
         */
        float minimumDistanceBetweenFeatures = 50;

        /**
         * Optical flow measures the tracking error for every feature.
         * If the point can’t be tracked or it’s out of the image it will set this error to a maximum value.
         * This threshold defines the level where the tracking accuracy is considered too bad to keep the point.
         */
        float lostFeatureErrorThreshold = 50000;

        /**
         * Once a feature was detected and we started tracking it, we need to update its Harris score on each image.
         * This is needed because a feature point can disappear, or it can become too weak to be tracked. This
         * threshold defines the point where such a feature must be dropped.
         * As the goal of the algorithm is to provide longer tracks, we try to add strong points and track them until
         * they are absolutely untrackable. This is why, this value is usually smaller than the detection threshold.
         */
        float trackedFeatureThreshold = 200000;
    };

    /**
     * Corner detector configuration.
     * Used for feature detection.
     */
    CornerDetector cornerDetector;

    /**
     * Motion estimator configuration.
     * Used for feature reidentification between current and previos features.
     */
    MotionEstimator motionEstimator;

    /**
     * FeatureMaintainer configuration.
     * Used for feature maintaining.
     */
    FeatureMaintainer featureMaintainer;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(FeatureTrackerConfigData::CornerDetector::Thresholds, initialValue, min, max, decreaseFactor, increaseFactor);
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(FeatureTrackerConfigData::CornerDetector, algorithmType, numImageCells, targetNumFeatures, maxNumFeatures, thresholds);
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
    FeatureTrackerConfigData::MotionEstimator, enable, algorithmType, pyramidLevels, searchWindowWidth, searchWindowHeight, epsilon, maxIterations);
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
    FeatureTrackerConfigData::FeatureMaintainer, enable, minimumDistanceBetweenFeatures, lostFeatureErrorThreshold, trackedFeatureThreshold);
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(FeatureTrackerConfigData, cornerDetector, motionEstimator, featureMaintainer);

/// RawFeatureTrackerConfig configuration structure
struct RawFeatureTrackerConfig : public RawBuffer {
    FeatureTrackerConfigData config;

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) const override {
        nlohmann::json j = *this;
        metadata = nlohmann::json::to_msgpack(j);
        datatype = DatatypeEnum::FeatureTrackerConfig;
    };

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(RawFeatureTrackerConfig, config);
};

}  // namespace dai
