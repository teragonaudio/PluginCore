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
      
      // First try loading from the root directory, and then from the user's home directory
      result = loadFromDirectory(getVstDirectory("/"));
      if(result == NULL) {
        result = loadFromDirectory(getVstDirectory(getHomeDirectory()));
      }
      
      return result;
    }
    
    Plugin* PluginLoaderMac::loadFromDirectory(const char* pluginPath) {
      return NULL;
    }
    
    const char* PluginLoaderMac::getVstDirectory(const char* rootSearchPath) {
      return NULL;
    }
    
    const char* PluginLoaderMac::getHomeDirectory() {
      return NULL;
    }
  }
}