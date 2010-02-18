#ifndef __VstWrapper_h__
#define __VstWrapper_h__

#ifndef __audioeffectx__
#include "audioeffectx.h"
#endif

#ifndef __Plugin_h__
#include "plugin/Plugin.h"
#endif

namespace teragon {
namespace plugincore {
  class VstWrapper : public AudioEffectX {
  public:
    VstWrapper(Plugin *plugin, audioMasterCallback audioMaster);
    ~VstWrapper();

    void processReplacing(float **inputs, float **outputs, VstInt32 sampleFrames);

  private:
    Plugin *plugin;
  };
}
}

#endif