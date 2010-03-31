#ifndef __VstWrapper_h__
#define __VstWrapper_h__

#ifndef __audioeffectx__
#include "audioeffectx.h"
#endif

#ifndef __Plugin_h__
#include "plugincore/plugin/Plugin.h"
#endif

namespace teragon {
namespace plugincore {
  // TODO: Should support user-defined channel counts.  For now, stereo is fine.
  const int kNumChannels = 2;

  class VstWrapper : public AudioEffectX {
  public:
    VstWrapper(Plugin *plugin, audioMasterCallback audioMaster);
    ~VstWrapper();

    void processReplacing(float **inputs, float **outputs, VstInt32 sampleFrames);

	  float getParameter(VstInt32 index);
	  void getParameterDisplay(VstInt32 index, char* text);
	  void getParameterName(VstInt32 index, char* text);
    void setParameter(VstInt32 index, float value);

  private:
    Plugin *plugin;
  };
}
}

#endif