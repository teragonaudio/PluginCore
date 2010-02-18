#ifndef __AudioBuffer_h__
#include "AudioBuffer.h"
#endif

namespace teragon {
namespace plugincore {
  class AudioBufferSet {
  public:
    AudioBufferSet(const BufferIndex numChannels, const BufferIndex size);
    ~AudioBufferSet();
    
    const Sample** getBuffers() { return 0; };
    void setBuffers(Sample** buffers) {};

    const Sample getSample(const BufferIndex channel, const BufferIndex index) { return 0.0; };
    void setSample(const BufferIndex channel, const BufferIndex index, const Sample value) {};
    
    const BufferIndex getSize() { return 0; };
    const BufferIndex getNumChannels() { return 0; };
  };
}
}