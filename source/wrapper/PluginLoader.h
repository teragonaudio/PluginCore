#ifndef __PluginLoader_h__
#define __PluginLoader_h__

#include <string>

#ifndef __Plugin_h__
#include "plugincore/plugin/Plugin.h"
#endif

#ifndef PLUGIN_LOCATION
#define PLUGIN_LOCATION ""
#endif

#if WINDOWS
#define VST24_EXTENSION "dll"
#elif MAC
#define VST24_EXTENSION "vst"
#endif

namespace teragon {
namespace plugincore {
  typedef Plugin*(PluginFactoryFuncPtr)(void);

  class PluginLoader {
  public:
    PluginLoader() {};
    virtual ~PluginLoader() {};

    virtual Plugin* load() = 0;
  };
}
}

#endif