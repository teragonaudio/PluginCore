/*
 *  AudioBuffer.h
 *  plugincore
 *
 *  Created by Nik Reiman on 2010-01-14.
 *  Copyright 2010 Singbox AB. All rights reserved.
 *
 */

namespace teragon {
namespace plugincore {
  typedef float Sample;
  typedef unsigned long BufferIndex;
  
	class AudioBuffer {
  public:
    AudioBuffer(const BufferIndex size);
    ~AudioBuffer();
    
    const Sample getSample(const BufferIndex index);
    void setSample(const BufferIndex index, const Sample value);
    
    const BufferIndex getSize();
	};
}
}