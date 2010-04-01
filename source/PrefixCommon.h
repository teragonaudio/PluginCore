#include <string>

// Definitions common to all PluginCore API
const std::string kPluginFactoryFunctionName = "createPluginInstance";

const char kFileDelimiter = '.';
const int kBufferStringSize = 1024;

// Load plugin definitions from the project
#include "PluginDefinition.h"

#ifndef PLUGIN_ID
#error PLUGIN_ID must be defined in your project's PluginDefinition.h file
#endif

#ifndef PLUGIN_NAME
#error PLUGIN_NAME must be defined in your project's PluginDefinition.h file
#endif

#ifndef PLUGIN_MANUFACTURER
#error PLUGIN_MANUFACTURER must be defined in your project's PluginDefinition.h file
#endif
