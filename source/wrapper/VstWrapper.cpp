#ifndef __VstWrapper_h__
#include "VstWrapper.h"
#endif

AudioEffect* createEffectInstance(audioMasterCallback audioMaster) {
	return new VstWrapper(audioMaster);
}

VstWrapper::VstWrapper(audioMasterCallback audioMaster) : AudioEffectX(audioMaster, 0, NUM_PARAMS) {
  if(audioMaster) {
    setNumInputs(NUM_INPUTS);
    setNumOutputs(NUM_OUTPUTS);
    setUniqueID(UNIQUE_ID);
    canProcessReplacing();
  }
}

VstWrapper::~VstWrapper() {
}

void VstWrapper::processReplacing(float **inputs, float **outputs, VstInt32 sampleFrames) {
}

