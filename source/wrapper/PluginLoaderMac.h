#ifndef __PluginLoaderMac_h__
#define __PluginLoaderMac_h__

#ifndef __PLuginLoader_h__
#include "PluginLoader.h"
#endif

namespace teragon {
namespace plugincore {
  typedef Plugin*(PluginEntryPoint)(void);
  
  class PluginLoaderMac : public PluginLoader {
  public:
    PluginLoaderMac();
    ~PluginLoaderMac();
    
    Plugin* load();
    
  private:
    Plugin* loadFromDirectory(std::string pluginPath);
    
    std::string getPluginLocationInBundleResources();
  };
}
}

#endif