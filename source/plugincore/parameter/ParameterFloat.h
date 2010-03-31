#ifndef __ParameterFloat_h__
#define __ParameterFloat_h__

#ifndef __PluginParameter_h__
#include "PluginParameter.h"
#endif

#include <sstream>

namespace teragon {
  namespace plugincore {
    class ParameterFloat : public PluginParameter {
    public:
      ParameterFloat(ParameterString name) : PluginParameter() {
        this->name = name;
        this->value = 0.0;
      }
      ~ParameterFloat() {}

      const ParameterString getName() const { return this->name; }
      const ParameterString getDisplayValue() const {
        std::stringstream numberFormatter;
        numberFormatter << this->value;
        return numberFormatter.str();
      }

      const ParameterValue getValue() const { return this->value; }
      void setValue(const ParameterValue value) { this->value = value; }

    private:
      ParameterString name;
      ParameterValue value;
    };
  }
}

#endif