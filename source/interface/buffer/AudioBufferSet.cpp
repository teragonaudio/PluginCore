/*
 *  AudioBufferSet.cpp
 *  plugincore
 *
 *  Created by Nik Reiman on 2010-02-13.
 *  Copyright 2010 Singbox AB. All rights reserved.
 *
 */

#include "AudioBufferSet.h"

namespace teragon {
namespace plugincore {
  AudioBufferSet::AudioBufferSet(const BufferIndex numChannels, const BufferIndex size) {
  }
  
  AudioBufferSet::~AudioBufferSet() {
  }
  
  const Sample AudioBufferSet::getSample(const BufferIndex channel, const BufferIndex index) {
    return 0.0;
  }
  
  void AudioBufferSet::setSample(const BufferIndex channel, const BufferIndex index, const Sample value) {
  }
  
  const BufferIndex AudioBufferSet::getSize() {
    return 0;
  }
  
  const BufferIndex AudioBufferSet::getNumChannels() {
    return 0;
  }
}
}