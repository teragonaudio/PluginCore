#ifndef __Plugin_h__
#define __Plugin_h__

#ifndef __AudioBufferSet_h__
#include "plugincore/buffer/AudioBufferSet.h"
#endif

namespace teragon {
namespace plugincore {
	class Plugin {
  public:
		Plugin();
		virtual ~Plugin();
		
		virtual void initialize() = 0;
		virtual void process(const AudioBufferSet& inputs, AudioBufferSet& outputs) = 0;
		
    virtual const int getNumInputs() const = 0;
    virtual const int getNumOutputs() const = 0;
    virtual const unsigned long getPluginId() const = 0;
    virtual const unsigned long getPluginManufacturerId() const = 0;
    virtual const int getNumPrograms() const = 0;

    virtual const int getNumParameters() const = 0;
	};
}
}

#endif