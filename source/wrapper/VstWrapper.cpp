#ifndef __VstWrapper_h__
#include "VstWrapper.h"
#endif

#ifndef __Plugin_h__
#include "plugin/Plugin.h"
#endif

#ifndef __PluginLoader_h__
#include "PluginLoader.h"
#endif

#if WINDOWS
#ifndef __PluginLoaderWindows_h__
#include "PluginLoaderWindows.h"
#endif
#endif

#if MAC
#ifndef __PluginLoaderMac_h__
#include "PluginLoaderMac.h"
#endif
#endif

AudioEffect* createEffectInstance(audioMasterCallback audioMaster) {
  teragon::plugincore::PluginLoader* pluginLoader = NULL;
#if WINDOWS
  pluginLoader = new PluginLoaderWindows();
#elif MAC
  pluginLoader = new PluginLoaderMac();
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
    AudioBufferSet inputSet(this->plugin->getNumInputs(), sampleFrames);
    AudioBufferSet outputSet(this->plugin->getNumOutputs(), sampleFrames);

    inputSet.setBuffers(static_cast<float**>(inputs));
    outputSet.setBuffers(static_cast<float**>(outputs));

    this->plugin->process(inputSet, outputSet);
  }
}
}