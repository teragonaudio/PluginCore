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
    ASSERT_EQ(NULL, audioBuffer.getBufferData());
  }

  // This is the standard use-case scenario -- take an existing array of floating
  // point values and push them into the buffer.  We should make sure that the size
  // and contents of the returned buffer are correct.
  TEST_F(AudioBufferTest, setBuffer) {
    AudioBuffer audioBuffer;
    audioBuffer.setBufferData(sampleData, kTestBufferSize);

    ASSERT_EQ(kTestBufferSize, audioBuffer.getSize());
    const Sample* testData = audioBuffer.getBufferData();
    for(BufferIndex i = 0; i < kTestBufferSize; ++i) {
      ASSERT_EQ(sampleData[i], testData[i]);
    }
  }

  // Should not reset an object's buffer data and size
  TEST_F(AudioBufferTest, setBufferToNull) {
    AudioBuffer audioBuffer;
    audioBuffer.setBufferData(sampleData, kTestBufferSize);
    audioBuffer.setBufferData(NULL, 1);
    ASSERT_EQ(kTestBufferSize, audioBuffer.getSize());
    for(BufferIndex i = 0; i < kTestBufferSize; ++i) {
      ASSERT_EQ(kTestSampleValue, audioBuffer.getSample(i));
    }
  }

  // Make sure that we can iterate over all samples in a buffer and that the value is correct
  TEST_F(AudioBufferTest, getSample) {
    AudioBuffer audioBuffer;
    audioBuffer.setBufferData(sampleData, kTestBufferSize);
    for(BufferIndex i = 0; i < kTestBufferSize; ++i) {
      ASSERT_EQ(kTestSampleValue, audioBuffer.getSample(i));
    }
  }

  // Should return 0 here, and definitely should NOT segfault or anything like that
  TEST_F(AudioBufferTest, getSampleBeyondBufferSize) {
    AudioBuffer audioBuffer;
    audioBuffer.setBufferData(sampleData, kTestBufferSize);
    ASSERT_EQ(0.0, audioBuffer.getSample(kTestBufferSize + 1));
  }

  // Should be able to set samples within the buffer
  TEST_F(AudioBufferTest, setSample) {
    AudioBuffer audioBuffer;
    audioBuffer.setBufferData(sampleData, kTestBufferSize);

    for(BufferIndex i = 0; i < kTestBufferSize; ++i) {
      audioBuffer.setSample(i, kTestSampleValue * (Sample)2.0);
      ASSERT_EQ(kTestSampleValue * 2.0, audioBuffer.getSample(i));
    }
  }

  // Should not segfault or corrupt the object's data
  TEST_F(AudioBufferTest, setSampleNegativeIndex) {
    AudioBuffer audioBuffer;
    audioBuffer.setBufferData(sampleData, kTestBufferSize);
    audioBuffer.setSample(-1, 0.0);
    for(BufferIndex i = 0; i < kTestBufferSize; ++i) {
      ASSERT_EQ(kTestSampleValue, audioBuffer.getSample(i));
    }
  }

  // Should not segfault or corrupt the object's data
  TEST_F(AudioBufferTest, setSampleInvalidIndex) {
    AudioBuffer audioBuffer;
    audioBuffer.setBufferData(sampleData, kTestBufferSize);
    audioBuffer.setSample(kTestBufferSize + 1, 0.0);
    for(BufferIndex i = 0; i < kTestBufferSize; ++i) {
      ASSERT_EQ(kTestSampleValue, audioBuffer.getSample(i));
    }
  }

  // Try setting the size of the buffer to a smaller value.  The data in the buffer should
  // remain the same, but the size should reflect the new value.
  TEST_F(AudioBufferTest, setSizeSmaller) {
    AudioBuffer audioBuffer;
    audioBuffer.setBufferData(sampleData, kTestBufferSize);
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
    // Use another data buffer which we can initialize to non-zero values
    Sample* dirtySampleData = new Sample[kTestBufferSize * 2];
    memset(dirtySampleData, 0xdeadbeef, kTestBufferSize * 2);
    audioBuffer.setBufferData(dirtySampleData, kTestBufferSize);
    audioBuffer.setSize(kTestBufferSize * 2);
    ASSERT_EQ(kTestBufferSize * 2, audioBuffer.getSize());
    for(BufferIndex i = 0; i < kTestBufferSize; ++i) {
      ASSERT_EQ(kTestSampleValue, audioBuffer.getSample(i));
    }
    for(BufferIndex i = kTestBufferSize; i < 10; ++i) {
      ASSERT_EQ(0, audioBuffer.getSample(kTestBufferSize + i));
    }

    // Also check the *raw* data, because getSample will return 0 if the index is larger than size
    const Sample* resultData = audioBuffer.getBufferData();
    for(BufferIndex i = kTestBufferSize; i < 10; ++i) {
      ASSERT_EQ(0, resultData[kTestBufferSize + i]);
    }
  }

  // Should not reset buffer or contents
  TEST_F(AudioBufferTest, setSizeToZero) {
    AudioBuffer audioBuffer;
    audioBuffer.setBufferData(sampleData, kTestBufferSize);
    audioBuffer.setSize(0);
    ASSERT_EQ(kTestBufferSize, audioBuffer.getSize());
    for(BufferIndex i = 0; i < kTestBufferSize; ++i) {
      ASSERT_EQ(kTestSampleValue, audioBuffer.getSample(i));
    }
  }

  // Obviously should not be permitted.  In this case we should also check to see that the
  // object's data is preserved
  TEST_F(AudioBufferTest, setSizeToNegativeValue) {
    AudioBuffer audioBuffer;
    audioBuffer.setBufferData(sampleData, kTestBufferSize);
    audioBuffer.setSize(-1);
    ASSERT_EQ(kTestBufferSize, audioBuffer.getSize());
    ASSERT_EQ(sampleData, audioBuffer.getBufferData());
  }
}
}