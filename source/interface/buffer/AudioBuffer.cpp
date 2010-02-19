#ifndef __AudioBuffer_h__
#include "AudioBuffer.h"
#endif

namespace teragon {
namespace plugincore {
  AudioBuffer::AudioBuffer() : buffer(NULL), size(0) {
  }
  
  AudioBuffer::~AudioBuffer() {
  }
  
  const Sample AudioBuffer::getSample(const BufferIndex index) {
    if(index > 0 && index < this->size) {
      return this->buffer[index];
    }
    else {
      return 0.0f;
    }
  }
  
  void AudioBuffer::setBufferData(Sample* value, const BufferIndex size) {
    if(value != NULL && size > 0) {
      this->buffer = value;
      this->size = size;
    }
  }

  void AudioBuffer::setSample(const BufferIndex index, const Sample value) {
  }

  void AudioBuffer::setSize(const BufferIndex value) {
    if(value > 0) {
      this->size = value;
    }
  }
}
}