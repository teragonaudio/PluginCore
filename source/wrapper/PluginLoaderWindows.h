#ifndef __PluginLoaderWindows_h__
#define __PluginLoaderWindows_h__

#ifndef __PluginLoader_h__
#include "PluginLoader.h"
#endif

namespace teragon {
namespace plugincore {
  class PluginLoaderWindows : public PluginLoader {
  public:
    PluginLoaderWindows();
    ~PluginLoaderWindows();

    Plugin* load();
  };
}
}

#endif