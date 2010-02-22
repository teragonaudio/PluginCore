#ifndef __PluginLoaderWindows_h__
#define __PluginLoaderWindows_h__

#ifndef __PluginLoader_h__
#include "wrapper/PluginLoader.h"
#endif

#ifndef DEFAULT_REGISTRY_LOCATION
#define kDefaultRegistryLocation "HKEY_LOCAL_MACHINE\\SOFTWARE\\Teragon Audio\\PluginCore"
#endif

namespace teragon {
namespace plugincore {
  class PluginLoaderWindows : public PluginLoader {
  public:
    PluginLoaderWindows();
    ~PluginLoaderWindows();

    Plugin* load();

    static const unsigned long kRegistryKeyBufferSize = 1024;

  protected:
    Plugin* loadWithRegistryKey();
    std::string getRegistryKey(const char* location, const char* keyName);

    
  };
}
}

#endif