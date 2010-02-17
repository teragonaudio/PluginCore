#include "VstWrapper.h"

AudioEffect* createEffectInstance(audioMasterCallback audioMaster) {
	return new VstWrapper(audioMaster);
}

VstWrapper::VstWrapper(audioMasterCallback audioMaster) : AudioEffectX(audioMaster, 0, NUM_PARAMS) {
}

VstWrapper::~VstWrapper() {
}

void VstWrapper::processReplacing(float **inputs, float **outputs, VstInt32 sampleFrames) {
}
