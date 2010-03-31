#ifndef __PluginParameter_h__
#define __PluginParameter_h__

#include <string>

namespace teragon {
  namespace plugincore {
    typedef float ParameterValue;
    typedef std::string ParameterName;

    class PluginParameter {
    public:
      PluginParameter() {};
      virtual ~PluginParameter() {};

      virtual ParameterName getName() const = 0;
      virtual const ParameterValue getValue() const = 0;
      virtual void setValue(const ParameterValue value) = 0;
    };
  }
}

#endif