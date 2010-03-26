#ifndef __PluginLoaderMac_h__
#include "PluginLoaderMac.h"
#endif

#include <dlfcn.h>

namespace teragon {
  namespace plugincore {
    PluginLoaderMac::PluginLoaderMac() : PluginLoader() {
    }
    
    PluginLoaderMac::~PluginLoaderMac() {
    }
    
    Plugin* PluginLoaderMac::load() {
      Plugin* result = NULL;
      
      result = loadFromDirectory(getPluginLocationInBundleResources());
      if(result == NULL) {
        result = loadFromDirectory(PLUGIN_LOCATION);
      }
      
      return result;
    }
    
    Plugin* PluginLoaderMac::loadFromDirectory(std::string pluginPath) {
      Plugin* result = NULL;
      
      void* dynamicLibraryHandle = dlopen(pluginPath.c_str(), RTLD_LAZY);
      if(dynamicLibraryHandle != NULL) {
        PluginEntryPoint* pluginEntryPoint = reinterpret_cast<PluginEntryPoint*>(dlsym(dynamicLibraryHandle, "createPlugin"));
        if(pluginEntryPoint != NULL) {
          result = pluginEntryPoint();
        }
      }
      
      return result;
    }
    
    std::string PluginLoaderMac::getPluginLocationInBundleResources() {
      std::string result = "";

      char* mylocation = getenv("PWD");
      
      CFArrayRef bundles = CFBundleGetAllBundles();
      for(int i = 0; i < CFArrayGetCount(bundles); ++i) {
        CFBundleRef bundle = (CFBundleRef)CFArrayGetValueAtIndex(bundles, i);
        printf("GOT %d:", i);
        if(bundle != NULL) {
          CFStringRef bundleName = CFBundleGetIdentifier(bundle);
          if(bundleName != NULL) {
            printf("%s", CFStringGetCStringPtr(bundleName, kCFStringEncodingMacRoman));
          }
        }
        printf("\n");
      }
      CFBundleRef bundleRef = CFBundleGetBundleWithIdentifier(CFSTR("org.teragon.ExampleEffect.vst"));
      CFURLRef resourceDirectoryUrl = CFBundleCopyResourcesDirectoryURL(bundleRef);
      char resultBuffer[1024];
      CFURLGetFileSystemRepresentation(resourceDirectoryUrl, true, (UInt8*)resultBuffer, 1024);
      result.assign(resultBuffer);
      result.append("/ExampleEffect.dylib");
      
      return result;
    }
  }
}