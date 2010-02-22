#ifndef __PluginLoaderMac_h__
#define __PluginLoaderMac_h__

#ifndef __PLuginLoader_h__
#include "PluginLoader.h"
#endif

namespace teragon {
namespace plugincore {
  class PluginLoaderMac : public PluginLoader {
  public:
    PluginLoaderMac() : PluginLoader() {};
    ~PluginLoaderMac() {};
  };
}
}

#endif