#ifndef __AudioBuffer_h__
#include "AudioBuffer.h"
#endif

namespace teragon {
namespace plugincore {
  class AudioBufferSet {
  public:
    AudioBufferSet();
    ~AudioBufferSet();
    
    AudioBuffer* getBuffer(const BufferIndex channel) const;
    const Sample** getBufferData() const;
    void setBufferData(Sample** value, const BufferIndex numChannels, const BufferIndex size);

    const Sample getSample(const BufferIndex channel, const BufferIndex index) const;
    void setSample(const BufferIndex channel, const BufferIndex index, const Sample value);
    
    const BufferIndex getNumChannels() const { return this->numChannels; };
    void setNumChannels(const BufferIndex value);

    const BufferIndex getSize() const;
    void setSize(const BufferIndex value);

  private:
    AudioBuffer** buffers;
    BufferIndex numChannels;
  };
}
}