TEST(MemoryTest, TexturePoolReuse) {
    RealTimePhotoEngine engine(1920, 1080);
    engine.initialize();
    
    size_t initialMemUsage = getGPUMemoryUsage();
    
    // Process 60 frames (1 second at 60fps)
    for (int i = 0; i < 60; i++) {
        GLuint testTex = createTestTexture();
        engine.processFrame(testTex, 0);
        releaseTexture(testTex);
    }
    
    size_t finalMemUsage = getGPUMemoryUsage();
    size_t memoryDelta = finalMemUsage - initialMemUsage;
    
    // Verify no memory growth
    EXPECT_LT(memoryDelta, 1024 * 1024);  // <1MB growth
    
    // Verify texture reuse
    EXPECT_EQ(engine.getTextureAllocCount(), 2);  // Only 2 persistent buffers
}
