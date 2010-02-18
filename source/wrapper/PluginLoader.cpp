#ifndef __PluginLoader_h__
#include "PluginLoader.h"
#endif

namespace teragon {
namespace plugincore {
  PluginLoader::PluginLoader() : pluginName() {
  }

  PluginLoader::~PluginLoader() {
  }

  Plugin* PluginLoader::load() {
    return load(findPluginName());
  }

  Plugin* PluginLoader::load(const std::string& libraryName) {
    return NULL;
  }

  const std::string& PluginLoader::findPluginName() {
    return getPluginName();
  }
}
}