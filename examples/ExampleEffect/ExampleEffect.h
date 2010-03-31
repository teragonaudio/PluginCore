/*
 *  ExampleEffect.h
 *  PluginCore
 *
 *  Created by Nik Reiman on 2010-03-26.
 *  Copyright 2010 Teragon Audio. All rights reserved.
 *
 */

#ifndef __ExampleEffect_h__
#define __ExampleEffect_h__

#ifndef __Plugin_h__
#include "plugincore/plugin/Plugin.h"
#endif

#ifndef __ParameterSetMap_h__
#include "plugincore/parameter/ParameterSetMap.h"
#endif

namespace teragon {
  class ExampleEffect : public teragon::plugincore::Plugin {
  public:
    ExampleEffect();
    ~ExampleEffect();    
    
    void initialize();
		void process(const teragon::plugincore::AudioBufferSet& inputs, teragon::plugincore::AudioBufferSet& outputs);
		
    const int getNumInputs() const { return 2; }
    const int getNumOutputs() const { return 2; }
    const unsigned long getPluginId() const { return 'exfx'; }
    const unsigned long getPluginManufacturerId() const { return 'Tera'; }
    const int getNumPrograms() const { return 0; }

    const teragon::plugincore::PluginParameterSet& getParameterSet() const { return this->parameters; }

  private:
    teragon::plugincore::ParameterSetMap parameters;
  };
}

#endif