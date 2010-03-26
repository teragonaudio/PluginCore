/*
 *  ExampleEffect.cpp
 *  PluginCore
 *
 *  Created by Nik Reiman on 2010-03-26.
 *  Copyright 2010 Teragon Audio. All rights reserved.
 *
 */

#ifndef __ExampleEffect_h__
#include "ExampleEffect.h"
#endif

namespace teragon {
  ExampleEffect::ExampleEffect() : teragon::plugincore::Plugin() {
  }
  
  ExampleEffect::~ExampleEffect() {
  }
  
  void ExampleEffect::initialize() {
  }
  
  void ExampleEffect::process(const teragon::plugincore::AudioBufferSet& inputs, teragon::plugincore::AudioBufferSet& outputs) {
  }
}