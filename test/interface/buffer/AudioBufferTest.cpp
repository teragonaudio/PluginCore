#include "interface/buffer/AudioBuffer.h"
#include "gtest/gtest.h"

namespace teragon {
namespace plugincore {
  const BufferIndex kTestBufferSize = 512;
  const Sample kTestSampleValue = 0.345f;

  class AudioBufferTest : public ::testing::Test {
  protected:
    virtual void SetUp() {
      sampleData = new Sample[kTestBufferSize];
      for(BufferIndex i = 0; i < kTestBufferSize; ++i) {
        sampleData[i] = kTestSampleValue;
      }
    }

    virtual void TearDown() {
      delete [] sampleData;
    }

    Sample *sampleData;
  };

  // Creating empty audio buffer should result in sane return values for getters
  TEST_F(AudioBufferTest, createEmptyBuffer) {
    AudioBuffer audioBuffer;
    ASSERT_EQ(0, audioBuffer.getSize());
    ASSERT_EQ(NULL, audioBuffer.getBuffer());
  }

  // This is the standard use case scenario -- take an existing array of floating
  // point values and push them into the buffer.  We should make sure that the size
  // is correct and that the memory location of the buffer is identical to our test
  // data array.
  TEST_F(AudioBufferTest, setBuffer) {
    AudioBuffer audioBuffer;
    audioBuffer.setBuffer(sampleData, kTestBufferSize);

    ASSERT_EQ(kTestBufferSize, audioBuffer.getSize());
    ASSERT_EQ(sampleData, audioBuffer.getBuffer());
  }

  // Should reset an object's buffer data and the size to 0
  TEST_F(AudioBufferTest, setBufferToNull) {
    AudioBuffer audioBuffer;
    audioBuffer.setBuffer(sampleData, kTestBufferSize);
    audioBuffer.setBuffer(NULL, 1);
    ASSERT_EQ(NULL, audioBuffer.getBuffer());
    ASSERT_EQ(0, audioBuffer.getSize());
  }

  // Make sure that we can iterate over all samples in a buffer and that the value is correct
  TEST_F(AudioBufferTest, getSample) {
    AudioBuffer audioBuffer;
    audioBuffer.setBuffer(sampleData, kTestBufferSize);
    for(BufferIndex i = 0; i < kTestBufferSize; ++i) {
      ASSERT_EQ(kTestSampleValue, audioBuffer.getSample(i));
    }
  }

  // Should return 0 here, and definitely should NOT segfault or anything like that
  TEST_F(AudioBufferTest, getSampleBeyondBufferSize) {
    AudioBuffer audioBuffer;
    audioBuffer.setBuffer(sampleData, kTestBufferSize);
    ASSERT_EQ(0.0, audioBuffer.getSample(kTestBufferSize + 1));
  }

  // Try resetting the size of the buffer to a smaller value.  The data in the buffer should
  // remain the same, but the size should reflect the new value.
  TEST_F(AudioBufferTest, setSizeSmaller) {
    AudioBuffer audioBuffer;
    audioBuffer.setBuffer(sampleData, kTestBufferSize);
    audioBuffer.setSize(kTestBufferSize - 10);
    ASSERT_EQ(kTestBufferSize - 10, audioBuffer.getSize());
    for(BufferIndex i = 0; i < audioBuffer.getSize(); ++i) {
      ASSERT_EQ(kTestSampleValue, audioBuffer.getSample(i));
    }
  }

  // Try increasing the size of the buffer.  In this case, the data already in the buffer should
  // remain untouched, but any samples added to the end of the buffer should be 0.
  TEST_F(AudioBufferTest, setSizeLarger) {
    AudioBuffer audioBuffer;
    audioBuffer.setBuffer(sampleData, kTestBufferSize);
    audioBuffer.setSize(kTestBufferSize + 10);
    ASSERT_EQ(kTestBufferSize + 10, audioBuffer.getSize());
    for(BufferIndex i = 0; i < kTestBufferSize; ++i) {
      ASSERT_EQ(kTestSampleValue, audioBuffer.getSample(i));
    }
    for(BufferIndex i = kTestBufferSize; i < 10; ++i) {
      ASSERT_EQ(0, audioBuffer.getSample(kTestBufferSize + i));
    }
  }

  // Should basically reset the buffer.  If there is existing data in the buffer, then it should
  // be set to null
  TEST_F(AudioBufferTest, setSizeToZero) {
    AudioBuffer audioBuffer;
    audioBuffer.setBuffer(sampleData, kTestBufferSize);
    audioBuffer.setSize(0);
    ASSERT_EQ(0, audioBuffer.getSize());
    ASSERT_EQ(NULL, audioBuffer.getBuffer());
  }

  // Obviously should not be permitted.  In this case we should also check to see that the
  // object's data is preserved
  TEST_F(AudioBufferTest, setSizeToNegativeValue) {
    AudioBuffer audioBuffer;
    audioBuffer.setBuffer(sampleData, kTestBufferSize);
    audioBuffer.setSize(-1);
    ASSERT_EQ(kTestBufferSize, audioBuffer.getSize());
    ASSERT_EQ(sampleData, audioBuffer.getBuffer());
  }
}
}