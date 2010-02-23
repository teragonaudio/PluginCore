#include <AudioUnit/AudioUnit.r>

#include "AudioUnitWrapperVersion.h"

// Note that resource IDs must be spaced 2 apart for the 'STR ' name and description
#define kAudioUnitResID_AudioUnitWrapper 1000

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ AudioUnitWrapper~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define RES_ID kAudioUnitResID_AudioUnitWrapper
#define COMP_TYPE kAudioUnitType_MusicDevice
#define COMP_SUBTYPE kAudioUnitWrapperComponentSubtype
#define COMP_MANUF kAudioUnitWrapperComponentManufacturer

#define VERSION kAudioUnitWrapperVersion
#define NAME "AudioUnitWrapper"
#define DESCRIPTION "AudioUnitWrapper AU"
#define ENTRY_POINT "AudioUnitWrapperEntry"

#include "AUResources.r"
