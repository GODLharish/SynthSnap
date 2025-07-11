TEST(LowLightEnhancementTest, DynamicRangeExpansion) {
    // Create dark input (4x4 low-light image)
    std::vector<float> input(16, 0.08f);
    // Add slight variation
    for (int i = 0; i < 16; i++) {
        input[i] += (i % 4) * 0.01f;
    }
    
    // Process enhancement
    std::vector<float> output = enhanceLowLightCPU(input);
    
    // Metrics verification
    float inputAvg = 0.0f, outputAvg = 0.0f;
    for (int i = 0; i < 16; i++) {
        inputAvg += input[i];
        outputAvg += output[i];
        // Verify shadow detail preservation
        if (input[i] < 0.1f) {
            EXPECT_GT(output[i], input[i] * 2.5f);  // Minimum gain
            EXPECT_LT(output[i], input[i] * 4.0f);  // Maximum gain
        }
    }
    inputAvg /= 16;
    outputAvg /= 16;
    
    // Verify brightness improvement
    EXPECT_GT(outputAvg, inputAvg * 2.8f);
    EXPECT_LT(outputAvg, inputAvg * 3.2f);
    
    // Verify no clipping
    for (float val : output) {
        EXPECT_GT(val, 0.0f);
        EXPECT_LT(val, 1.0f);
    }
}
