#ifndef __AudioBuffer_h__
#define __AudioBuffer_h__

#include <stdlib.h>

namespace teragon {
namespace plugincore {
  typedef float Sample;
  typedef long BufferIndex;
  
  /** Class which represents a single channel of floating-point audio data */
	class AudioBuffer {
  public:
    AudioBuffer();
    ~AudioBuffer();
    
    const Sample* getBufferData() const { return this->buffer; };
    void setBufferData(Sample* value, const BufferIndex size);

    const Sample getSample(const BufferIndex index) const;
    void setSample(const BufferIndex index, const Sample value);
    
    const BufferIndex getSize() const { return this->size; };
    void setSize(const BufferIndex value);

  private:
    void initializeBuffer(Sample* source, const BufferIndex sourceSize, const BufferIndex newSize);

    Sample* buffer;
    BufferIndex size;
	};
}
}

#endif