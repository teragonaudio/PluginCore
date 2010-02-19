#include "interface/buffer/AudioBufferSet.h"
#include "gtest/gtest.h"

namespace teragon {
namespace plugincore {
  const BufferIndex kTestBufferSize = 512;
  const BufferIndex kTestBufferChannels = 2;
  const Sample kTestSampleValue = 0.345f;

  class AudioBufferSetTest : public ::testing::Test {
  protected:
    virtual void SetUp() {
      sampleData = new Sample*[kTestBufferChannels];
      for(BufferIndex i = 0; i < kTestBufferChannels; ++i) {
        sampleData[i] = new Sample[kTestBufferSize];
        for(BufferIndex j = 0; j < kTestBufferSize; ++j) {
          sampleData[i][j] = kTestSampleValue;
        }
      }
    }

    void assertSampleDataEquals(AudioBufferSet& resultBufferSet) {
      ASSERT_EQ(kTestBufferChannels, resultBufferSet.getNumChannels());
      ASSERT_EQ(kTestBufferSize, resultBufferSet.getSize());
      for(BufferIndex i = 0; i < kTestBufferChannels; ++i) {
        for(BufferIndex j = 0; j < kTestBufferSize; ++j) {
          ASSERT_EQ(sampleData[i][j], resultBufferSet.getSample(i, j));
        }
      }
    }

    virtual void TearDown() {
      delete [] sampleData;
    }

    Sample **sampleData;
  };

  // A new buffer should have sane default return values for getters
  TEST_F(AudioBufferSetTest, createEmptyBufferSet) {
    AudioBufferSet audioBufferSet;
    ASSERT_EQ(NULL, audioBufferSet.getBufferData());
    ASSERT_EQ(0, audioBufferSet.getNumChannels());
    ASSERT_EQ(0, audioBufferSet.getSize());
  }

  // This is the standard use-case scenario.  We pass a set of floating point arrays
  // to the buffer set after initialization, and expect that the channel count, size,
  // and contents contain the data.
  TEST_F(AudioBufferSetTest, setBuffers) {
    AudioBufferSet audioBufferSet;
    audioBufferSet.setBufferData(sampleData, kTestBufferChannels, kTestBufferSize);
    ASSERT_EQ(kTestBufferChannels, audioBufferSet.getNumChannels());
    ASSERT_EQ(kTestBufferSize, audioBufferSet.getSize());
    
    const Sample** testData = audioBufferSet.getBufferData();
    for(BufferIndex i = 0; i < kTestBufferChannels; ++i) {
      for(BufferIndex j = 0; j < kTestBufferSize; ++j) {
        ASSERT_EQ(sampleData[i][j], testData[i][j]);
      }
    }
  }

  // Should set sample data, channels, size
  TEST_F(AudioBufferSetTest, getSample) {
    AudioBufferSet audioBufferSet;
    audioBufferSet.setBufferData(sampleData, kTestBufferChannels, kTestBufferSize);
    assertSampleDataEquals(audioBufferSet);
  }

  // Should return valid audio buffers for each channel
  TEST_F(AudioBufferSetTest, getBuffer) {
    AudioBufferSet audioBufferSet;
    audioBufferSet.setBufferData(sampleData, kTestBufferChannels, kTestBufferSize);
    for(BufferIndex i = 0; i < kTestBufferChannels; ++i) {
      AudioBuffer* audioBuffer = audioBufferSet.getBuffer(i);
      ASSERT_TRUE(audioBuffer != NULL);
      for(BufferIndex j = 0; j < kTestBufferSize; ++j) {
        ASSERT_EQ(kTestSampleValue, audioBuffer->getSample(j));
      }
    }
  }

  // Should return null pointer
  TEST_F(AudioBufferSetTest, getBufferNegativeChannel) {
    AudioBufferSet audioBufferSet;
    audioBufferSet.setBufferData(sampleData, kTestBufferChannels, kTestBufferSize);
    AudioBuffer *audioBuffer = audioBufferSet.getBuffer(-1);
    ASSERT_EQ(NULL, audioBuffer);
  }

  // Should return null pointer
  TEST_F(AudioBufferSetTest, getBufferInvalidChannel) {
    AudioBufferSet audioBufferSet;
    audioBufferSet.setBufferData(sampleData, kTestBufferChannels, kTestBufferSize);
    AudioBuffer *audioBuffer = audioBufferSet.getBuffer(kTestBufferChannels + 1);
    ASSERT_EQ(NULL, audioBuffer);
  }

  // Should return 0 if given an invalid channel
  TEST_F(AudioBufferSetTest, getSampleNegativeChannel) {
    AudioBufferSet audioBufferSet;
    audioBufferSet.setBufferData(sampleData, kTestBufferChannels, kTestBufferSize);
    ASSERT_EQ(0.0, audioBufferSet.getSample(-1, 0));
  }

  // Should return 0 if given an invalid channel
  TEST_F(AudioBufferSetTest, getSampleInvaidChannel) {
    AudioBufferSet audioBufferSet;
    audioBufferSet.setBufferData(sampleData, kTestBufferChannels, kTestBufferSize);
    ASSERT_EQ(0.0, audioBufferSet.getSample(kTestBufferChannels + 1, 0));
  }

  // Should return 0 if given an invalid index
  TEST_F(AudioBufferSetTest, getSampleNegativeIndex) {
    AudioBufferSet audioBufferSet;
    audioBufferSet.setBufferData(sampleData, kTestBufferChannels, kTestBufferSize);
    ASSERT_EQ(0.0, audioBufferSet.getSample(0, -1));
  }

  // Should return 0 if given an invalid index
  TEST_F(AudioBufferSetTest, getSampleInvalidIndex) {
    AudioBufferSet audioBufferSet;
    audioBufferSet.setBufferData(sampleData, kTestBufferChannels, kTestBufferSize);
    ASSERT_EQ(0.0, audioBufferSet.getSample(0, kTestBufferSize + 1));
  }

  TEST_F(AudioBufferSetTest, setSample) {
    AudioBufferSet audioBufferSet;
    audioBufferSet.setBufferData(sampleData, kTestBufferChannels, kTestBufferSize);
    for(BufferIndex i = 0; i < kTestBufferChannels; ++i) {
      for(BufferIndex j = 0; j < kTestBufferSize; ++j) {
        audioBufferSet.setSample(i, j, kTestSampleValue * (Sample)2.0);
        ASSERT_EQ(kTestSampleValue * 2.0, audioBufferSet.getSample(i, j));
      }
    }
  }

  // Should not segfault or reset object data
  TEST_F(AudioBufferSetTest, setSampleNegativeChannel) {
    AudioBufferSet audioBufferSet;
    audioBufferSet.setBufferData(sampleData, kTestBufferChannels, kTestBufferSize);
    audioBufferSet.setSample(-1, 0, 0.0);
    assertSampleDataEquals(audioBufferSet);
  }

  // Should not segfault or reset object data
  TEST_F(AudioBufferSetTest, setSampleInvalidChannel) {
    AudioBufferSet audioBufferSet;
    audioBufferSet.setBufferData(sampleData, kTestBufferChannels, kTestBufferSize);
    audioBufferSet.setSample(kTestBufferChannels + 1, 0, 0.0);
    assertSampleDataEquals(audioBufferSet);
  }

  // Should not segfault or reset object data
  TEST_F(AudioBufferSetTest, setSampleNegativeIndex) {
    AudioBufferSet audioBufferSet;
    audioBufferSet.setBufferData(sampleData, kTestBufferChannels, kTestBufferSize);
    audioBufferSet.setSample(0, -1, 0.0);
    assertSampleDataEquals(audioBufferSet);
  }

  // Should not segfault or reset object data
  TEST_F(AudioBufferSetTest, setSampleInvalidIndex) {
    AudioBufferSet audioBufferSet;
    audioBufferSet.setBufferData(sampleData, kTestBufferChannels, kTestBufferSize);
    audioBufferSet.setSample(0, kTestBufferSize + 1, 0.0);
    assertSampleDataEquals(audioBufferSet);
  }

  // Should not segfault or reset object data
  TEST_F(AudioBufferSetTest, setNumChannelsToZero) {
    AudioBufferSet audioBufferSet;
    audioBufferSet.setBufferData(sampleData, kTestBufferChannels, kTestBufferSize);
    audioBufferSet.setNumChannels(0);
    assertSampleDataEquals(audioBufferSet);
  }

  // Should not segfault or reset object data
  TEST_F(AudioBufferSetTest, setNumChannelsNegativeValue) {
    AudioBufferSet audioBufferSet;
    audioBufferSet.setBufferData(sampleData, kTestBufferChannels, kTestBufferSize);
    audioBufferSet.setNumChannels(-1);
    assertSampleDataEquals(audioBufferSet);
  }

  // Should create a new audio buffer which is the same size as the other buffers in the
  // buffer set, and with properly initialized data
  TEST_F(AudioBufferSetTest, setNumChannelsToGreaterValue) {
    AudioBufferSet audioBufferSet;
    audioBufferSet.setBufferData(sampleData, kTestBufferChannels, kTestBufferSize);
    audioBufferSet.setNumChannels(kTestBufferChannels + 1);
    ASSERT_EQ(kTestBufferChannels + 1, audioBufferSet.getNumChannels());
    
    // All data in the other buffers should be unchanged
    ASSERT_EQ(kTestBufferSize, audioBufferSet.getSize());
    for(BufferIndex i = 0; i < kTestBufferChannels; ++i) {
      for(BufferIndex j = 0; j < kTestBufferSize; ++j) {
        ASSERT_EQ(sampleData[i][j], audioBufferSet.getSample(i, j));
      }
    }
    
    // Make sure that the new channel is properly zero-initialized
    AudioBuffer* resultBuffer = audioBufferSet.getBuffer(kTestBufferChannels);
    ASSERT_TRUE(resultBuffer != NULL);
    ASSERT_EQ(kTestBufferSize, resultBuffer->getSize());
    for(BufferIndex i = 0; i < kTestBufferSize; ++i) {
      ASSERT_EQ(0.0, resultBuffer->getSample(i));
    }
  }

  // Should truncate buffer set, but data should be preserved
  TEST_F(AudioBufferSetTest, setNumChannelsToSmallerValue) {
    AudioBufferSet audioBufferSet;
    audioBufferSet.setBufferData(sampleData, kTestBufferChannels, kTestBufferSize);
    audioBufferSet.setNumChannels(kTestBufferChannels + 1);
    ASSERT_EQ(kTestBufferChannels + 1, audioBufferSet.getNumChannels());
    AudioBuffer* resultBuffer = audioBufferSet.getBuffer(kTestBufferChannels);
    ASSERT_TRUE(resultBuffer != NULL);
    ASSERT_EQ(kTestBufferSize, resultBuffer->getSize());
    for(BufferIndex i = 0; i < kTestBufferSize; ++i) {
      ASSERT_EQ(0.0, resultBuffer->getSample(i));
    }
  }

  // Should expand size of all buffers in the set and initialize values beyond last sample to zero
  TEST_F(AudioBufferSetTest, setSizeToGreaterValue) {
    AudioBufferSet audioBufferSet;
    // Use another data buffer which we can initialize to non-zero values
    Sample** dirtySampleData = new Sample*[kTestBufferChannels];
    for(BufferIndex i = 0; i < kTestBufferChannels; ++i) {
      dirtySampleData[i] = new Sample[kTestBufferSize * 2];
      memset(dirtySampleData[i], 0xdeadbeef, kTestBufferSize * 2);
      for(BufferIndex j = 0; j < kTestBufferSize; ++j) {
        dirtySampleData[i][j] = kTestSampleValue;
      }
    }
    audioBufferSet.setBufferData(dirtySampleData, kTestBufferChannels, kTestBufferSize);

    audioBufferSet.setSize(kTestBufferSize * 2);
    ASSERT_EQ(kTestBufferSize * 2, audioBufferSet.getSize());
    for(BufferIndex i = 0; i < kTestBufferChannels; ++i) {
      AudioBuffer* resultBuffer = audioBufferSet.getBuffer(i);
      ASSERT_TRUE(resultBuffer != NULL);
      ASSERT_EQ(kTestBufferSize * 2, resultBuffer->getSize());
      // The first part of the buffer should be the same
      for(BufferIndex j = 0; j < kTestBufferSize; ++j) {
        ASSERT_EQ(kTestSampleValue, resultBuffer->getSample(j));
      }
      // The second part of the buffer should contain zero-initialized samples
      for(BufferIndex j = kTestBufferSize; j < kTestBufferSize; ++j) {
        ASSERT_EQ(0.0, resultBuffer->getSample(j));
      }
    }
  }

  // Should truncate all samples in buffer set
  TEST_F(AudioBufferSetTest, setSizeToSmallerValue) {
    AudioBufferSet audioBufferSet;
    audioBufferSet.setBufferData(sampleData, kTestBufferChannels, kTestBufferSize);
    audioBufferSet.setSize(kTestBufferSize / 2);
    ASSERT_EQ(kTestBufferSize / 2, audioBufferSet.getSize());
    for(BufferIndex i = 0; i < kTestBufferChannels; ++i) {
      AudioBuffer* resultBuffer = audioBufferSet.getBuffer(i);
      ASSERT_EQ(kTestBufferSize / 2, resultBuffer->getSize());
      for(BufferIndex j = 0; j < kTestBufferSize / 2; ++j) {
        ASSERT_EQ(kTestSampleValue, resultBuffer->getSample(j));
      }
    }
  }

  // Should not segfault or reset object data
  TEST_F(AudioBufferSetTest, setSizeToZero) {
    AudioBufferSet audioBufferSet;
    audioBufferSet.setBufferData(sampleData, kTestBufferChannels, kTestBufferSize);
    audioBufferSet.setSize(0);
    assertSampleDataEquals(audioBufferSet);
  }

  // Should not segfault or reset object data
  TEST_F(AudioBufferSetTest, setSizeNegativeValue) {
    AudioBufferSet audioBufferSet;
    audioBufferSet.setBufferData(sampleData, kTestBufferChannels, kTestBufferSize);
    audioBufferSet.setSize(-1);
    assertSampleDataEquals(audioBufferSet);
  }
}
}