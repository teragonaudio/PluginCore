/*
 *  AudioBufferSet.h
 *  plugincore
 *
 *  Created by Nik Reiman on 2010-02-13.
 *  Copyright 2010 Singbox AB. All rights reserved.
 *
 */

#include "AudioBuffer.h"

namespace teragon {
namespace plugincore {
  class AudioBufferSet {
  public:
    AudioBufferSet(const BufferIndex numChannels, const BufferIndex size);
    ~AudioBufferSet();
    
    const Sample getSample(const BufferIndex channel, const BufferIndex index);
    void setSample(const BufferIndex channel, const BufferIndex index, const Sample value);
    
    const BufferIndex getSize();
    const BufferIndex getNumChannels();
  };
}
}