#include "wrapper/PluginLoaderWindows.h"
#include "gtest/gtest.h"

#if WINDOWS
namespace teragon {
namespace plugincore {
  class PluginLoaderWindowsMock : public PluginLoaderWindows {
  public:
    PluginLoaderWindowsMock() : PluginLoaderWindows() {};
    ~PluginLoaderWindowsMock() {};

    // Protected methods which are made public for testing
    std::string getRegistryKey(const char* location, const char* keyName) {
      return PluginLoaderWindows::getRegistryKey(location, keyName);
    }
  };

  TEST(PluginLoaderWindows, getRegistryKey) {
    PluginLoaderWindowsMock pluginLoader;
    std::string result = pluginLoader.getRegistryKey(kDefaultRegistryLocation, "test");
    ASSERT_TRUE(result == "c:\\Views\\VstPlugins");
  }
}
}
#endif