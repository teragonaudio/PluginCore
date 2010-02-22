#ifndef __PluginLoaderWindows_h__
#include "PluginLoaderWindows.h"
#endif

#include <Windows.h>
#include <string>

namespace teragon {
namespace plugincore {
  PluginLoaderWindows::PluginLoaderWindows() : PluginLoader() {
  }

  PluginLoaderWindows::~PluginLoaderWindows() {
  }

  Plugin* PluginLoaderWindows::load() {
    Plugin* result = NULL;

    result = loadWithRegistryKey();

    return result;
  }

  Plugin* PluginLoaderWindows::loadWithRegistryKey() {
    Plugin* result = NULL;

    std::string pluginLocation = getRegistryKey(kDefaultRegistryLocation, "test");//getShortLibraryName());

    return result;
  }

  std::string PluginLoaderWindows::getRegistryKey(const char* location, const char* keyName) {
    HKEY key;
    TCHAR value[kRegistryKeyBufferSize]; 
    DWORD bufLen = 1024*sizeof(TCHAR);
    long ret;
    ret = RegOpenKeyExA(HKEY_LOCAL_MACHINE, location, 0, KEY_QUERY_VALUE, &key);
    if( ret != ERROR_SUCCESS ){
        return std::string();
    }
    ret = RegQueryValueExA(key, keyName, 0, 0, (LPBYTE) value, &bufLen);
    RegCloseKey(key);
    if ( (ret != ERROR_SUCCESS) || (bufLen > 1024*sizeof(TCHAR)) ){
        return std::string();
    }
    std::string stringValue = std::string((char*)value);//, (size_t)bufLen - 1);
    size_t i = stringValue.length();
    while(i > 0 && stringValue[i - 1] == '\0') {
      --i;
    }
    return stringValue.substr(0,i); 
  }
}
}