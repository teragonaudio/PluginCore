#ifndef __AudioBuffer_h__
#define __AudioBuffer_h__

namespace teragon {
namespace plugincore {
  typedef float Sample;
  typedef unsigned long BufferIndex;
  
	class AudioBuffer {
  public:
    AudioBuffer();
    ~AudioBuffer();
    
    const Sample* getBuffer() { return 0; };
    void setBuffer(Sample* value, const BufferIndex size);

    const Sample getSample(const BufferIndex index);
    void setSample(const BufferIndex index, const Sample value);
    
    const BufferIndex getSize() { return 0; };
    void setSize(const BufferIndex index) {};
	};
}
}

#endif