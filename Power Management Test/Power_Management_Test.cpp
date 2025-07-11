TEST(PowerTest, DynamicVoltageScaling) {
    RealTimePhotoEngine engine(1920, 1080);
    engine.initialize();
    
    // Measure baseline power
    float powerBaseline = measurePowerConsumption();
    
    // Simulate thermal throttling
    simulateThermalStress(85.0f);  // 85°C
    
    // Process frame in throttled mode
    engine.processFrame(testTexture);
    float powerThrottled = measurePowerConsumption();
    
    // Verify power reduction
    EXPECT_LT(powerThrottled, powerBaseline * 0.8f);
    
    // Verify quality metrics
    float qualityScore = engine.getLastFrameQuality();
    EXPECT_GT(qualityScore, 0.7f);  // Maintain 70%+ quality
}
