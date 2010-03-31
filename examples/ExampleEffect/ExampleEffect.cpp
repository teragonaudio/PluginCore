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

extern "C" {
  teragon::plugincore::Plugin* createPluginInstance() {
    return new ExampleEffect();
  }
};

ExampleEffect::ExampleEffect() : teragon::plugincore::Plugin(), parameters() {
}

ExampleEffect::~ExampleEffect() {
}

void ExampleEffect::initialize() {
}

void ExampleEffect::process(const teragon::plugincore::AudioBufferSet& inputs, teragon::plugincore::AudioBufferSet& outputs) {
  for(int channel = 0; channel < inputs.getNumChannels(); ++channel) {
    for(int frame = 0; frame < inputs.getSize(); ++frame) {
      outputs.setSample(channel, frame, inputs.getSample(channel, frame));
    }
  }
}
