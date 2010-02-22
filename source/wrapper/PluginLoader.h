#ifndef __PluginLoader_h__
#define __PluginLoader_h__

#include <string>

#ifndef __Plugin_h__
#include "plugincore/plugin/Plugin.h"
#endif

namespace teragon {
namespace plugincore {
  class PluginLoader {
  public:
    PluginLoader() {};
    virtual ~PluginLoader() {};

    virtual Plugin* load() = 0;
  };
}
}

#endif