/*
 *  AudioBuffer.cpp
 *  plugincore
 *
 *  Created by Nik Reiman on 2010-02-13.
 *  Copyright 2010 Singbox AB. All rights reserved.
 *
 */

#include "AudioBuffer.h"

namespace teragon {
namespace plugincore {
  AudioBuffer::AudioBuffer(const BufferIndex size) {
  }
  
  AudioBuffer::~AudioBuffer() {
  }
  
  const Sample AudioBuffer::getSample(const BufferIndex index) {
    return 0.0f;
  }
  
  void AudioBuffer::setSample(const BufferIndex index, const Sample value) {
  }
  
  const BufferIndex AudioBuffer::getSize() {
    return 0;
  }
}
}