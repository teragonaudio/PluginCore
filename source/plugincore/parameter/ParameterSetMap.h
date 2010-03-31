#ifndef __ParameterSetMap_h__
#define __ParameterSetMap_h__

#ifndef __PluginParameterSet_h__
#include "plugincore/parameter/PluginParameterSet.h"
#endif

#include <map>

namespace teragon {
  namespace plugincore {
    typedef std::map<ParameterName, PluginParameter*> ParameterSetMapStorage;

    class ParameterSetMap : public PluginParameterSet {
    public:
      ParameterSetMap();
      ~ParameterSetMap();

      PluginParameter* getParameter(const ParameterName name) const;
      const int size() const;

    private:
      ParameterSetMapStorage parameterStorage;
    };
  }
}

#endif