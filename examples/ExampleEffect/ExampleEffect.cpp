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

#ifndef __ParameterFloat_h__
#include "plugincore/parameter/ParameterFloat.h"
#endif

extern "C" {
  teragon::plugincore::Plugin* createPluginInstance() {
    return new ExampleEffect();
  }
};

ExampleEffect::ExampleEffect() : teragon::plugincore::Plugin(), parameters() {
  initialize();
}

ExampleEffect::~ExampleEffect() {
}

void ExampleEffect::initialize() {
  parameters.addParameter(new teragon::plugincore::ParameterFloat("Gain"));
}

void ExampleEffect::process(const teragon::plugincore::AudioBufferSet& inputs, teragon::plugincore::AudioBufferSet& outputs) {
  teragon::plugincore::PluginParameter* gainParameter = parameters.getParameter("Gain");
  float gain = static_cast<float>(gainParameter->getValue());

  for(int channel = 0; channel < inputs.getNumChannels(); ++channel) {
    for(int frame = 0; frame < inputs.getSize(); ++frame) {
      teragon::plugincore::Sample input = inputs.getSample(channel, frame);
      teragon::plugincore::Sample output = input * gain;
      outputs.setSample(channel, frame, output);
    }
  }
}
