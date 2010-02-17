#include "audioeffectx.h"

#define NUM_PARAMS 0

class VstWrapper : public AudioEffectX {
public:
  VstWrapper(audioMasterCallback audioMaster);
  ~VstWrapper();

  void processReplacing(float **inputs, float **outputs, VstInt32 sampleFrames);
};