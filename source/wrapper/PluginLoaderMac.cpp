#ifndef __PluginLoaderMac_h__
#include "PluginLoaderMac.h"
#endif

namespace teragon {
  namespace plugincore {
    PluginLoaderMac::PluginLoaderMac() : PluginLoader() {
    }
    
    PluginLoaderMac::~PluginLoaderMac() {
    }
    
    Plugin* PluginLoaderMac::load() {
      Plugin* result = NULL;
      
      // First try loading from the root directory, then from the user's home directory,
      // and then from the location defined in PLUGIN_LOCATION, which may be overridden
      // in your build settings
      result = loadFromDirectory(getVstDirectory(NULL));
      if(result == NULL) {
        result = loadFromDirectory(getVstDirectory(getHomeDirectory()));
        if(result == NULL) {
          result = loadFromDirectory(PLUGIN_LOCATION);
        }
      }
      
      return result;
    }
    
    Plugin* PluginLoaderMac::loadFromDirectory(std::string pluginPath) {
      return NULL;
    }
    
    std::string PluginLoaderMac::getVstDirectory(std::string rootSearchPath) {
      if(rootSearchPath.empty()) {
        rootSearchPath = "";
      }
      return rootSearchPath.append("/Library/Plug-Ins/VST");
    }
    
    std::string PluginLoaderMac::getHomeDirectory() {
      return getenv("HOME");
    }
  }
}