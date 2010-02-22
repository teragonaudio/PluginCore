#ifndef __AudioBufferSet_h__
#include "AudioBufferSet.h"
#endif

namespace teragon {
namespace plugincore {
  AudioBufferSet::AudioBufferSet() : buffers(NULL), numChannels(0) {
  }
  
  AudioBufferSet::~AudioBufferSet() {
    for(BufferIndex i = 0; i < getNumChannels(); ++i) {
      delete buffers[i];
    }
    delete [] buffers;
  }

  AudioBuffer* AudioBufferSet::getBuffer(const BufferIndex channel) const {
    if(channel >= 0 && channel < getNumChannels()) {
      return buffers[channel];
    }
    else {
      return NULL;
    }
  }

  const Sample** AudioBufferSet::getBufferData() const {
    if(getNumChannels() > 0) {
      const Sample** result = new const Sample*[numChannels];
      for(BufferIndex i = 0; i < getNumChannels(); ++i) {
        result[i] = buffers[i]->getBufferData();
      }
      return result;
    }
    else {
      return NULL;
    }
  }

  const Sample AudioBufferSet::getSample(const BufferIndex channel, const BufferIndex index) const {
    if(channel >= 0 && channel < getNumChannels()) {
      return buffers[channel]->getSample(index);
    }
    else {
      return 0.0;
    }
  }

  const BufferIndex AudioBufferSet::getSize() const {
    if(getNumChannels() > 0) {
      return buffers[0]->getSize();
    }
    else {
      return 0;
    }
  }

  void AudioBufferSet::setBufferData(Sample** value, const BufferIndex numChannels, const BufferIndex size) {
    if(numChannels > 0 && size > 0) {
      // Clear out any existing data and reinitialize
      delete [] buffers;
      this->numChannels = numChannels;
      buffers = new AudioBuffer*[numChannels];
      for(BufferIndex i = 0; i < numChannels; ++i) {
        AudioBuffer* buffer = new AudioBuffer();
        buffer->setBufferData(value[i], size);
        buffers[i] = buffer;
      }
    }
  }

  void AudioBufferSet::setSample(const BufferIndex channel, const BufferIndex index, const Sample value) {
    if(channel >= 0 && channel < getNumChannels() && index >= 0 && index < getSize()) {
      buffers[channel]->setSample(index, value);
    }
  }

  void AudioBufferSet::setNumChannels(const BufferIndex value) {
    // Make sure that the new channel count is positive and not equal to the current
    // channel count in order to save resizing
    if(value > 0 && value != getNumChannels()) {
      BufferIndex oldNumChannels = getNumChannels();
      this->numChannels = value;
      // If the new value is smaller than the current channel count, then delete extra channels
      if(this->numChannels < oldNumChannels) {
        for(BufferIndex i = this->numChannels; i < oldNumChannels; ++i) {
          delete buffers[i];
        }
      }
      // If the new value is larger, then initialize any channels and copy the old channels
      // into the new channels buffer
      else {
        AudioBuffer** oldBuffers = buffers;
        AudioBuffer** newBuffers = new AudioBuffer*[this->numChannels];
        for(BufferIndex i = 0; i < this->numChannels; ++i) {
          if(i < oldNumChannels) {
            newBuffers[i] = oldBuffers[i];
          }
          else {
            AudioBuffer* buffer = new AudioBuffer();
            // We are guaranteed to have at least one channel by this point
            buffer->setSize(oldBuffers[0]->getSize());
            newBuffers[i] = buffer;
          }
        }

        // Delete old channel buffers array
        buffers = newBuffers;
        delete [] oldBuffers;
      }
    }
  }

  void AudioBufferSet::setSize(const BufferIndex value) {
    if(value > 0 && value != getSize()) {
      for(BufferIndex i = 0; i < getNumChannels(); ++i) {
        buffers[i]->setSize(value);
      }
    }
  }
}
}