#define WINDOWS 1
#define WIN32 1
#define _WINDOWS 1
#define VSTWRAPPER_EXPORTS 1
#define _CRT_SECURE_NO_WARNINGS 1

#include "PluginDefinition.h"

#ifndef PLUGIN_NAME
#error PLUGIN_NAME must be defined in your project's PluginDefinition.h file
#endif

#ifndef PLUGIN_MANUFACTURER
#error PLUGIN_MANUFACTURER must be defined in your project's PluginDefinition.h file
#endif