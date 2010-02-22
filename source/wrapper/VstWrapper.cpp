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
  return new teragon::plugincore::VstWrapper(plugin, audioMaster);
}

namespace teragon {
namespace plugincore {
  VstWrapper::VstWrapper(Plugin *plugin, audioMasterCallback audioMaster) :
  AudioEffectX(audioMaster, plugin->getNumPrograms(), plugin->getNumParameters()) {
    this->plugin = plugin;

    if(audioMaster) {
      setNumInputs(plugin->getNumInputs());
      setNumOutputs(plugin->getNumOutputs());
      setUniqueID(plugin->getPluginId());
      canProcessReplacing();
    }

    plugin->initialize();
  }

  VstWrapper::~VstWrapper() {
    // Unload actual plugin library
    delete plugin;
  }

  void VstWrapper::processReplacing(float **inputs, float **outputs, VstInt32 sampleFrames) {
    AudioBufferSet inputSet, outputSet;
    inputSet.setBufferData(static_cast<float**>(inputs), this->plugin->getNumInputs(), sampleFrames);
    outputSet.setBufferData(static_cast<float**>(outputs), this->plugin->getNumOutputs(), sampleFrames);

    this->plugin->process(inputSet, outputSet);
  }
}
}