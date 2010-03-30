#ifndef __PluginLoaderWindows_h__
#include "wrapper/PluginLoaderWindows.h"
#endif

#if WINDOWS
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

    result = loadFromFile(getPluginLocationInRegistry());
    if(result == NULL) {
      result = loadFromFile(getPluginLocationInProgramFiles());
    }

    return result;
  }

  std::string PluginLoaderWindows::getPluginLocationInRegistry() {
    std::string result = "";

    return result;
  }

  std::string PluginLoaderWindows::getPluginLocationInProgramFiles() {
    std::string result = "";

    return result;
  }

  Plugin* PluginLoaderWindows::loadFromFile(std::string pluginLocation) {
    Plugin* result = NULL;

    if(pluginLocation.size() > 0) {
      LPCTSTR pluginLocationForWinApi = reinterpret_cast<LPCTSTR>(pluginLocation.c_str());
      if(pluginLocationForWinApi != NULL) {
        HMODULE module = LoadLibrary(pluginLocationForWinApi);
      }
    }

    return result;
  }

  std::string PluginLoaderWindows::getRegistryKey(const char* location, const char* keyName) {
    HKEY key;
    TCHAR value[kRegistryKeyBufferSize]; 
    DWORD bufLen = 1024*sizeof(TCHAR);
    long ret;
    ret = RegOpenKeyExA(HKEY_LOCAL_MACHINE, location, 0, KEY_QUERY_VALUE, &key);
    if( ret != ERROR_SUCCESS ){
      TCHAR error_msg[1024];
      FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, ret,  0, error_msg, 1024, NULL);
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
#endif