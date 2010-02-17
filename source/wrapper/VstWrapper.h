#ifndef __VstWrapper_h__
#define __VstWrapper_h__

#include "audioeffectx.h"

#define NUM_PARAMS 0
#define NUM_INPUTS 2
#define NUM_OUTPUTS 2
#define UNIQUE_ID 'VstW'

class VstWrapper : public AudioEffectX {
public:
  VstWrapper(audioMasterCallback audioMaster);
  ~VstWrapper();

  void processReplacing(float **inputs, float **outputs, VstInt32 sampleFrames);
};

#endif