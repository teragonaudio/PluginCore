#ifndef __VstWrapper_h__
#include "VstWrapper.h"
#endif

#ifndef __Plugin_h__
#include "plugin/Plugin.h"
#endif

#ifndef __PluginLoader_h__
#include "PluginLoader.h"
#endif

AudioEffect* createEffectInstance(audioMasterCallback audioMaster) {
  teragon::plugincore::PluginLoader PluginLoader;
  teragon::plugincore::Plugin* plugin = PluginLoader.load();
  return new teragon::plugincore::VstWrapper(PluginLoader.load(), audioMaster);
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
  }

  VstWrapper::~VstWrapper() {
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