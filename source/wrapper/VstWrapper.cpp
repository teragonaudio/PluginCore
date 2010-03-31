#ifndef __VstWrapper_h__
#include "wrapper/VstWrapper.h"
#endif

#ifndef __Plugin_h__
#include "plugincore/plugin/Plugin.h"
#endif

#ifndef __PluginLoader_h__
#include "wrapper/PluginLoader.h"
#endif

#if WINDOWS
#ifndef __PluginLoaderWindows_h__
#include "wrapper/PluginLoaderWindows.h"
#endif
#endif

#if MAC
#ifndef __PluginLoaderMac_h__
#include "wrapper/PluginLoaderMac.h"
#endif
#endif

AudioEffect* createEffectInstance(audioMasterCallback audioMaster) {
  teragon::plugincore::PluginLoader* pluginLoader = NULL;
#if WINDOWS
  pluginLoader = new teragon::plugincore::PluginLoaderWindows();
#elif MAC
  pluginLoader = new teragon::plugincore::PluginLoaderMac();
#endif
  teragon::plugincore::Plugin* plugin = pluginLoader->load();
  delete pluginLoader;
  
  return (plugin != NULL) ? new teragon::plugincore::VstWrapper(plugin, audioMaster) : NULL;
}

namespace teragon {
namespace plugincore {
  VstWrapper::VstWrapper(Plugin *plugin, audioMasterCallback audioMaster) :
    AudioEffectX(audioMaster, 0, plugin->getParameterSet().size()) {
    this->plugin = plugin;

    if(audioMaster) {
      setNumInputs(kNumChannels);
      setNumOutputs(kNumChannels);
      setUniqueID(PLUGIN_ID);
      canProcessReplacing();
    }
  }

  VstWrapper::~VstWrapper() {
    // Unload actual plugin library
    delete plugin;
  }

  void VstWrapper::processReplacing(float **inputs, float **outputs, VstInt32 sampleFrames) {
    AudioBufferSet inputSet, outputSet;
    inputSet.setBufferData(static_cast<float**>(inputs), kNumChannels, sampleFrames);
    outputSet.setNumChannels(inputSet.getNumChannels());
    outputSet.setSize(inputSet.getSize());
    this->plugin->process(inputSet, outputSet);
    for(int i = 0; i < outputSet.getNumChannels(); ++i) {
      memcpy(outputs[i], outputSet.getBuffer(i)->getBufferData(), sizeof(float) * sampleFrames);
    }
  }

  float VstWrapper::getParameter(VstInt32 index) {
    PluginParameter* parameter = plugin->getParameterSet().getParameter(index);
    return (parameter != NULL) ? static_cast<float>(parameter->getValue()) : 0.0f;
  }

  void VstWrapper::getParameterDisplay(VstInt32 index, char* text) {
    PluginParameter* parameter = plugin->getParameterSet().getParameter(index);
    if(parameter != NULL) {
      ParameterString displayValue = parameter->getDisplayValue();
      strncpy(text, displayValue.c_str(), kVstMaxParamStrLen);
      text[displayValue.size()] = '\0';
    }
  }

  void VstWrapper::getParameterName(VstInt32 index, char* text) {
    PluginParameter* parameter = plugin->getParameterSet().getParameter(index);
    if(parameter != NULL) {
      ParameterString name = parameter->getName();
      strncpy(text, name.c_str(), kVstMaxParamStrLen);
      text[name.size()] = '\0';
    }
  }

  void VstWrapper::setParameter(VstInt32 index, float value) {
    PluginParameter* parameter = plugin->getParameterSet().getParameter(index);
    if(parameter != NULL) {
      parameter->setValue(value);
    }
  }
}
}