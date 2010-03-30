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
    std::string pluginLocationRegistryKey = kSoftwareRegistryKey;
    pluginLocationRegistryKey.append(1, kDirectoryDelimiter);
    pluginLocationRegistryKey.append(PLUGIN_MANUFACTURER);
    pluginLocationRegistryKey.append(1, kDirectoryDelimiter);
    pluginLocationRegistryKey.append(PLUGIN_NAME);

    return getRegistryKey(pluginLocationRegistryKey, kPluginLocationRegistryKey);
  }

  /**
   * \return Full path to the plugin's expected library location in the Program Files directory,
   * which should look something like:
   * C:\Program Files\Your Company Name\PluginName\PluginName.dll
   * Where the company and plugin name are defined in the PluginDefinition.h file which your
   * project should have defined.
   */
  std::string PluginLoaderWindows::getPluginLocationInProgramFiles() {
    std::string result = "";

    char programFilesLocation[kBufferStringSize];
    LPCSTR programFilesKey = reinterpret_cast<LPCSTR>(kProgramFilesEnvKey.c_str());
    if(GetEnvironmentVariable(programFilesKey, (LPSTR)programFilesLocation, kBufferStringSize) > 0) {
      result.assign(programFilesLocation);
      result.append(1, kDirectoryDelimiter);
      result.append(PLUGIN_MANUFACTURER);
      result.append(1, kDirectoryDelimiter);
      result.append(PLUGIN_NAME);
      result.append(1, kDirectoryDelimiter);
      result.append(PLUGIN_NAME);
      result.append(1, kFileDelimiter);
      result.append(kVst24Extension);
    }

    return result;
  }

  /**
   * Instantiates a plugin object from a dynamic library
   * \param pluginLocation Full path to plugin, including extension
   * \return Initialized Plugin interface object, or else NULL if the plugin could not be loaded
   */
  Plugin* PluginLoaderWindows::loadFromFile(std::string pluginLocation) {
    Plugin* result = NULL;

    try {
      if(pluginLocation.size() == 0) {
        throw 1;
      }

      LPCTSTR pluginLocationForWinApi = reinterpret_cast<LPCTSTR>(pluginLocation.c_str());
      if(pluginLocationForWinApi == NULL) {
        throw 2;
      }

      HMODULE module = LoadLibrary(pluginLocationForWinApi);
      if(module == NULL) {
        throw 3;
      }

      FARPROC pluginFactoryAddress = GetProcAddress(module, kPluginFactoryFunctionName.c_str());
      if(pluginFactoryAddress == NULL) {
        throw 4;
      }

      PluginFactoryFuncPtr* pluginFactory = reinterpret_cast<PluginFactoryFuncPtr*>(pluginFactoryAddress);
      if(pluginFactory == NULL) {
        throw 5;
      }
      
      result = pluginFactory();
    }
    catch(int e) {
      DWORD errorCode = GetLastError();
      printf("Error loading plugin from file: %d, error code %d\n", e, errorCode);
    }

    return result;
  }

  std::string PluginLoaderWindows::getRegistryKey(std::string location, std::string keyName) {
    HKEY key;
    TCHAR value[kRegistryKeyBufferSize]; 
    DWORD bufferLen = kBufferStringSize * sizeof(TCHAR);
    long ret = RegOpenKeyExA(HKEY_LOCAL_MACHINE, location.c_str(), 0, KEY_QUERY_VALUE, &key);

    if(ret != ERROR_SUCCESS) {
      TCHAR error_msg[kBufferStringSize];
      FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, ret,  0, error_msg, kBufferStringSize, NULL);
      return std::string();
    }

    ret = RegQueryValueExA(key, keyName.c_str(), 0, 0, (LPBYTE) value, &bufferLen);
    RegCloseKey(key);
    if((ret != ERROR_SUCCESS) || (bufferLen > kBufferStringSize * sizeof(TCHAR))) {
        return std::string();
    }

    std::string stringValue = reinterpret_cast<char*>(value);
    size_t i = stringValue.length();
    while(i > 0 && stringValue[i - 1] == '\0') {
      --i;
    }

    return stringValue.substr(0,i); 
  }
}
}
#endif