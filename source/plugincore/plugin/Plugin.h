#ifndef __Plugin_h__
#define __Plugin_h__

#ifndef __AudioBufferSet_h__
#include "plugincore/buffer/AudioBufferSet.h"
#endif

#ifndef __PluginParameterSet_h__
#include "plugincore/parameter/PluginParameterSet.h"
#endif

namespace teragon {
namespace plugincore {
	class Plugin {
  public:
		Plugin() {};
		virtual ~Plugin() {};
		
		virtual void process(const AudioBufferSet& inputs, AudioBufferSet& outputs) = 0;
    virtual const PluginParameterSet& getParameterSet() const = 0;
	};
}
}

#endif