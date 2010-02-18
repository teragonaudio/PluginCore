#ifndef __AudioBuffer_h__
#define __AudioBuffer_h__

#include <stdlib.h>

namespace teragon {
namespace plugincore {
  typedef float Sample;
  typedef long BufferIndex;
  
	class AudioBuffer {
  public:
    AudioBuffer();
    ~AudioBuffer();
    
    const Sample* getBuffer() { return this->buffer; };
    void setBuffer(Sample* value, const BufferIndex size);

    const Sample getSample(const BufferIndex index);
    void setSample(const BufferIndex index, const Sample value);
    
    const BufferIndex getSize() { return this->size; };
    void setSize(const BufferIndex value);

  private:
    Sample* buffer;
    BufferIndex size;
	};
}
}

#endif