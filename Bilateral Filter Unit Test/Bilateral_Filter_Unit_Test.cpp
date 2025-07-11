#include <gtest/gtest.h>
#include "photo_engine.h"

TEST(BilateralFilterTest, NoiseReduction) {
    // Create test input (4x4 grayscale image with noise)
    const int width = 4, height = 4;
    std::vector<float> input = {
        0.1f, 0.9f, 0.2f, 0.8f,
        0.3f, 0.7f, 0.4f, 0.6f,
        0.2f, 0.8f, 0.1f, 0.9f,
        0.4f, 0.6f, 0.3f, 0.7f
    };
    
    // Process with bilateral filter
    std::vector<float> output = applyBilateralCPU(input, width, height, 1.5f);
    
    // Expected output (smoothed while preserving edges)
    std::vector<float> expected = {
        0.18f, 0.82f, 0.22f, 0.78f,
        0.28f, 0.72f, 0.38f, 0.62f,
        0.22f, 0.78f, 0.18f, 0.82f,
        0.32f, 0.68f, 0.28f, 0.72f
    };
    
    // Verify noise reduction while preserving contrast
    for (int i = 0; i < width*height; i++) {
        EXPECT_NEAR(output[i], expected[i], 0.05f);
        // Verify edge preservation
        if (i % width == 1) {  // Vertical edge positions
            EXPECT_GT(fabs(output[i] - output[i-1]), 0.4f);
        }
    }
}
