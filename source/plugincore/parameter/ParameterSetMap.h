#ifndef __ParameterSetMap_h__
#define __ParameterSetMap_h__

#ifndef __PluginParameterSet_h__
#include "plugincore/parameter/PluginParameterSet.h"
#endif

#include <map>

namespace teragon {
  namespace plugincore {
    typedef std::map<ParameterString, PluginParameter*> ParameterSetMapStorage;

    class ParameterSetMap : public PluginParameterSet {
    public:
      ParameterSetMap();
      ~ParameterSetMap();

      void addParameter(PluginParameter* parameter);

      PluginParameter* getParameter(const ParameterIndex index) const;
      PluginParameter* getParameter(const ParameterString name) const;
      
      const int size() const;

    private:
      ParameterSetMapStorage parameterStorage;
    };
  }
}

#endif