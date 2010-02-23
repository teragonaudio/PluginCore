#include "MusicDeviceBase.h"
#include "AudioUnitWrapperVersion.h"

namespace teragon {
  namespace plugincore {
    class AudioUnitWrapper : public MusicDeviceBase {
    public:
      AudioUnitWrapper(ComponentInstance inComponentInstance);
      ~AudioUnitWrapper();
      
      OSStatus Initialize();
      OSStatus Version() { return kAudioUnitWrapperVersion; }
      
      OSStatus GetParameterInfo(AudioUnitScope inScope, AudioUnitParameterID inParameterID, AudioUnitParameterInfo &outParameterInfo);
      ComponentResult StartNote(MusicDeviceInstrumentID inInstrument, MusicDeviceGroupID inGroupID,
                                NoteInstanceID *outNoteInstanceID, UInt32 inOffsetSampleFrame,
                                const MusicDeviceNoteParams &inParams);
      ComponentResult StopNote(MusicDeviceGroupID inGroupID, NoteInstanceID inNoteInstanceID, UInt32 inOffsetSampleFrame);
      bool StreamFormatWritable(AudioUnitScope scope, AudioUnitElement element);
  };  
}
}