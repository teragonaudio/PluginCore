#ifndef __AudioBuffer_h__
#include "AudioBuffer.h"
#endif

namespace teragon {
namespace plugincore {
  AudioBuffer::AudioBuffer(const BufferIndex size) {
  }
  
  AudioBuffer::~AudioBuffer() {
  }
  
  const Sample AudioBuffer::getSample(const BufferIndex index) {
    return 0.0f;
  }
  
  void AudioBuffer::setSample(const BufferIndex index, const Sample value) {
  }
  
  const BufferIndex AudioBuffer::getSize() {
    return 0;
  }
}
}