#ifndef __AudioUnitWrapperVersion_h__
#define __AudioUnitWrapperVersion_h__

#ifdef DEBUG
#define kAudioUnitWrapperVersion 0xFFFFFFFF
#else
#define kAudioUnitWrapperVersion 0x00010000	
#endif

#define kAudioUnitWrapperComponentSubtype 'Pass'
#define kAudioUnitWrapperComponentManufacturer 'Demo'

#endif
