#ifndef __PluginParameterSet_h__
#define __PluginParameterSet_h__

#ifndef __PluginParameter_h__
#include "plugincore/parameter/PluginParameter.h"
#endif

namespace teragon {
  namespace plugincore {
    class PluginParameterSet {
    public:
      PluginParameterSet() {};
      virtual ~PluginParameterSet() {};

      virtual PluginParameter* getParameter(const ParameterName name) const = 0;
      virtual const int size() const = 0;
    };
  }
}

#endif