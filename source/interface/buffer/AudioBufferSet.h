#ifndef __AudioBuffer_h__
#include "AudioBuffer.h"
#endif

namespace teragon {
namespace plugincore {
  class AudioBufferSet {
  public:
    AudioBufferSet();
    ~AudioBufferSet();
    
    AudioBuffer* getBuffer(const BufferIndex channel) const { return NULL; };
    const Sample** getBuffers() { return 0; };
    void setBuffers(Sample** buffers, const BufferIndex numChannels, const BufferIndex size) {};

    const Sample getSample(const BufferIndex channel, const BufferIndex index) { return 0.0; };
    void setSample(const BufferIndex channel, const BufferIndex index, const Sample value) {};
    
    const BufferIndex getNumChannels() const { return 0; };
    void setNumChannels(const BufferIndex value) {};

    const BufferIndex getSize() const { return 0; };
    void setSize(const BufferIndex value) {};

  private:
    AudioBuffer* buffers;
  };
}
}