#ifndef __PluginParameterSet_h__
#define __PluginParameterSet_h__

#ifndef __PluginParameter_h__
#include "plugincore/parameter/PluginParameter.h"
#endif

namespace teragon {
  namespace plugincore {
    typedef int ParameterIndex;

    class PluginParameterSet {
    public:
      PluginParameterSet() {};
      virtual ~PluginParameterSet() {};

      virtual void addParameter(PluginParameter* parameter) = 0;
      
      virtual PluginParameter* getParameter(const ParameterIndex index) const = 0;
      virtual PluginParameter* getParameter(const ParameterString name) const = 0;
      
      virtual const int size() const = 0;
    };
  }
}

#endif