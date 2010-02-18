#ifndef __AudioBuffer_h__
#define __AudioBuffer_h__

namespace teragon {
namespace plugincore {
  typedef float Sample;
  typedef unsigned long BufferIndex;
  
	class AudioBuffer {
  public:
    AudioBuffer(const BufferIndex size);
    ~AudioBuffer();
    
    const Sample* getBuffer();
    void setBuffer(Sample* value);

    const Sample getSample(const BufferIndex index);
    void setSample(const BufferIndex index, const Sample value);
    
    const BufferIndex getSize();
	};
}
}

#endif