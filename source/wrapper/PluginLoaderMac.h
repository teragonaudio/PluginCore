#ifndef __PluginLoaderMac_h__
#define __PluginLoaderMac_h__

#ifndef __PLuginLoader_h__
#include "PluginLoader.h"
#endif

namespace teragon {
namespace plugincore {
  class PluginLoaderMac : public PluginLoader {
  public:
    PluginLoaderMac();
    ~PluginLoaderMac();
    
    Plugin* load();
    
  private:
    Plugin* loadFromDirectory(const char* pluginPath);
    
    const char* getVstDirectory(const char* rootSearchPath);
    const char* getHomeDirectory();
  };
}
}

#endif