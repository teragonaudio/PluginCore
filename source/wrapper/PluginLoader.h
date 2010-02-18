#ifndef __PluginLoader_h__
#define __PluginLoader_h__

#include <string>

#ifndef __Plugin_h__
#include "plugin/Plugin.h"
#endif

namespace teragon {
namespace plugincore {
  class PluginLoader {
  public:
    PluginLoader();
    ~PluginLoader();

    Plugin* load();
    Plugin* load(const std::string& libraryName);

    const std::string& getPluginName() const { return this->pluginName; };

  private:
    const std::string& findPluginName();

    std::string pluginName;
  };
}
}

#endif