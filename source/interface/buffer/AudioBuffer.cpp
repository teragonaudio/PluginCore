#ifndef __AudioBuffer_h__
#include "AudioBuffer.h"
#endif

namespace teragon {
namespace plugincore {
  AudioBuffer::AudioBuffer() : buffer(NULL), size(0) {
  }
  
  AudioBuffer::~AudioBuffer() {
    delete [] buffer;
  }
  
  const Sample AudioBuffer::getSample(const BufferIndex index) const {
    if(index >= 0 && index < this->size) {
      return this->buffer[index];
    }
    else {
      return 0.0f;
    }
  }
  
  void AudioBuffer::setBufferData(Sample* value, const BufferIndex size) {
    if(value != NULL && size > 0) {
      initializeBuffer(value, size, size);
    }
  }

  void AudioBuffer::setSample(const BufferIndex index, const Sample value) {
    if(index >= 0 && index < this->size) {
      this->buffer[index] = value;
    }
  }

  void AudioBuffer::setSize(const BufferIndex value) {
    // Make sure that the new size is positive and not the same as our current size,
    // to avoid doing unnecessary work.
    if(value > 0 && value != this->size) {
      initializeBuffer(this->buffer, this->size, value);
    }
  }

  void AudioBuffer::initializeBuffer(Sample* source, const BufferIndex sourceSize, const BufferIndex newSize) {
    // Keep a reference to oldBuffer in case this buffer is being resized.  That way we can
    // copy from the old buffer to the new one and delete this buffer afterwards.
    Sample* oldBuffer = this->buffer;
    this->size = newSize;
    this->buffer = new Sample[newSize];

    // Copy source buffer to the new buffer, up until the lesser of the two buffer sizes.
    // This could potentially be SSE optimized.
    for(BufferIndex i = 0; i < sourceSize && i < newSize; ++i) {
      this->buffer[i] = source[i];
    }

    // If the size is bigger than the source buffer's size, then initialize new samples to 0.
    if(newSize > sourceSize) {
      for(BufferIndex i = sourceSize; i < newSize; ++i) {
        this->buffer[i] = 0.0;
      }
    }

    delete [] oldBuffer;
  }
}
}