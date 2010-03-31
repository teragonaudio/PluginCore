#ifndef __PluginLoaderWindows_h__
#include "wrapper/PluginLoaderWindows.h"
#endif

#if WINDOWS
#include <Windows.h>
#include <string>

#ifndef __PluginLoaderException_h__
#include "PluginLoaderException.h"
#endif

#ifndef __WindowsErrorException_h__
#include "WindowsErrorException.h"
#endif

namespace teragon {
namespace plugincore {
  PluginLoaderWindows::PluginLoaderWindows() : PluginLoader() {
  }

  PluginLoaderWindows::~PluginLoaderWindows() {
  }

  /**
   * Attempts to load the plugin library file using the following strategy:
   * 1. Load plugin from location specified in Windows registry
   * 2. Load plugin from Program Files directory
   * \return Initialized plugin instance, or NULL if the plugin could not be loaded
   */
  Plugin* PluginLoaderWindows::load() {
    Plugin* result = NULL;

    result = loadFromFile(getPluginLocationInRegistry());
    if(result == NULL) {
      result = loadFromFile(getPluginLocationInProgramFiles());
    }

    return result;
  }

  /**
   * \return Full path to the plugin's expected library location based on a key read from
   * the Windows registry.  The key is read from a location which looks something like this:
   * \\HKEY_LOCAL_MACHINE\SOFTWARE\Your Company Name\PluginName\PluginCoreLibPath
   * Where the company and plugin name are defined in the PluginDefinition.h file which your
   * project should have defined.
   */
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
        throw PluginLoaderException("Plugin location is empty");
      }

      LPCTSTR pluginLocationForWinApi = reinterpret_cast<LPCTSTR>(pluginLocation.c_str());
      if(pluginLocationForWinApi == NULL) {
        throw PluginLoaderException("Plugin location could not be converted to Windows API format");
      }

      HMODULE module = LoadLibrary(pluginLocationForWinApi);
      if(module == NULL) {
        throw WindowsErrorException(GetLastError());
      }

      FARPROC pluginFactoryAddress = GetProcAddress(module, kPluginFactoryFunctionName.c_str());
      if(pluginFactoryAddress == NULL) {
        throw WindowsErrorException(GetLastError());
      }

      PluginFactoryFuncPtr* pluginFactory = reinterpret_cast<PluginFactoryFuncPtr*>(pluginFactoryAddress);
      if(pluginFactory == NULL) {
        throw PluginLoaderException("Plugin factory address not valid");
      }
      
      result = pluginFactory();
    }
    catch(std::exception &error) {
      printf("Error loading plugin from file: %s\n", error.what());
    }

    return result;
  }

  /**
   * Reads a string-based key from the Windows registry.  The key must be located under the
   * HKEY_LOCAL_MACHINE root.
   * \param location Path to key
   * \param keyName Name of key to read
   * \return String value of key, or an empty string if an error occurred
   */
  std::string PluginLoaderWindows::getRegistryKey(std::string location, std::string keyName) {
    std::string result = "";

    try {
      // Open the actual registry key
      HKEY key;
      DWORD status = RegOpenKeyExA(HKEY_LOCAL_MACHINE, location.c_str(), 0, KEY_QUERY_VALUE, &key);
      if(status != ERROR_SUCCESS) {
        throw WindowsErrorException(status);
      }

      // Determine the size of the key's value
      char keyValue[kRegistryKeyBufferSize];
      DWORD bufferLen;
      status = RegQueryValueExA(key, keyName.c_str(), 0, 0, (LPBYTE)keyValue, &bufferLen);
      RegCloseKey(key);
      if(status != ERROR_SUCCESS) {
        throw WindowsErrorException(status);
      }

      result = keyValue;
    }
    catch(std::exception& error) {
      printf("Error getting plugin location from registry: %s\n", error.what());
    }

    return result;
  }
}
}
#endif