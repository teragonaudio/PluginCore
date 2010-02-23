#ifndef __AudioUnitWrapper_h__
#include "AudioUnitWrapper.h"
#endif

namespace teragon {
  namespace plugincore {
    COMPONENT_ENTRY(AudioUnitWrapper);

    AudioUnitWrapper::AudioUnitWrapper(ComponentInstance inComponentInstance) : MusicDeviceBase(inComponentInstance, 0, 2, 0, 0) {
    }
    
    AudioUnitWrapper::~AudioUnitWrapper() {
    }
    
    OSStatus AudioUnitWrapper::Initialize() {
      return noErr;
    }
    
    OSStatus AudioUnitWrapper::GetParameterInfo(AudioUnitScope inScope, AudioUnitParameterID inParameterID, AudioUnitParameterInfo &outParameterInfo) {
      return noErr;
    }
    
    ComponentResult AudioUnitWrapper::StartNote(MusicDeviceInstrumentID inInstrument, MusicDeviceGroupID inGroupID,
                              NoteInstanceID *outNoteInstanceID, UInt32 inOffsetSampleFrame,
                                                const MusicDeviceNoteParams &inParams) {
      return noErr;
    }
    
    ComponentResult AudioUnitWrapper::StopNote(MusicDeviceGroupID inGroupID, NoteInstanceID inNoteInstanceID, UInt32 inOffsetSampleFrame) {
      return noErr;
    }
    
    bool AudioUnitWrapper::StreamFormatWritable(AudioUnitScope scope, AudioUnitElement element) {
      return true;
    }
  }
}